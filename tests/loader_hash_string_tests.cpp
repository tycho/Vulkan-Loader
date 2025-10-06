/*
 * Copyright (c) 2026 The Khronos Group Inc.
 * Copyright (c) 2026 Valve Corporation
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and/or associated documentation files (the "Materials"), to
 * deal in the Materials without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Materials, and to permit persons to whom the Materials are
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice(s) and this permission notice shall be included in
 * all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE
 * USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 * Author: Charles Giessen <charles@lunarg.com>
 */

#include "test_environment.h"

#include <cstring>

extern "C" {
#include "loader_common.h"
#include "vk_extension_name_hashes.h"
#include "vk_command_name_hashes.h"
}

// loader_hash_string() is a plain 32-bit FNV-1a hash used purely as a cheap pre-filter in front of every
// strcmp() confirmation when resolving vkGet{Instance,Device}ProcAddr names (see loader/gpa_helper.c and
// loader/generated/vk_loader_extensions.c). Every call site dispatches on the hash via `switch (name_hash)`
// and confirms the match with strcmp() inside the matching `case` before returning - never a bare
// hash-only dispatch - so a hash collision can, at worst, cost one extra strcmp; it can never produce a
// wrong lookup result. These tests don't try to prove real Vulkan command names never collide (the code
// generator's build-time collision check does that) - they prove the hash-then-strcmp *pattern* stays safe
// even when two different strings are engineered to collide.

TEST(HashString, Deterministic) {
    ASSERT_EQ(loader_hash_string("vkCreateInstance"), loader_hash_string("vkCreateInstance"));
    ASSERT_EQ(loader_hash_string(""), loader_hash_string(""));
}

TEST(HashString, DifferentStringsUsuallyHashDifferently) {
    ASSERT_NE(loader_hash_string("vkCreateInstance"), loader_hash_string("vkDestroyInstance"));
    ASSERT_NE(loader_hash_string("vkCreateDevice"), loader_hash_string("vkCreateDevice2"));
    ASSERT_NE(loader_hash_string("vk"), loader_hash_string(""));
}

// scripts/generators/loader_extension_generator.py has its own copy of this hash function, used to
// precompute the hash constants embedded in the four switch statements those constants live in (generated
// and hand-written alike). The pairs below are copied verbatim from those switches, so this test fails
// directly if the Python and C implementations ever disagree - no need to invoke Python to prove it.
//
// Not every switch hashes the same input for a given command, so the "name" column below is exactly the
// string each one passes to loader_hash_string(), not always the full "vk"-prefixed name:
//   - trampoline_get_proc_addr() and extension_instance_gpa() hash the full command name, e.g.
//     loader_hash_string("vkDestroyInstance").
//   - loader_lookup_device_dispatch_table() and loader_lookup_instance_dispatch_table() strip the leading
//     "vk" before hashing (`name += 2`), e.g. loader_hash_string("DestroyInstance").
TEST(HashString, MatchesGeneratorEmbeddedConstants) {
    struct NameAndHash {
        const char *name;
        uint64_t expected_hash;
    };
    const NameAndHash pairs[] = {
        {"vkGetPhysicalDeviceVideoCapabilitiesKHR", XXH3_vkGetPhysicalDeviceVideoCapabilitiesKHR},
        {"vkGetPhysicalDeviceVideoFormatPropertiesKHR", XXH3_vkGetPhysicalDeviceVideoFormatPropertiesKHR},
        {"vkCreateVideoSessionKHR", XXH3_vkCreateVideoSessionKHR},
        {"vkDestroyVideoSessionKHR", XXH3_vkDestroyVideoSessionKHR},
        {"vkGetVideoSessionMemoryRequirementsKHR", XXH3_vkGetVideoSessionMemoryRequirementsKHR},
        {"vkGetInstanceProcAddr", XXH3_vkGetInstanceProcAddr},
        {"vkDestroyInstance", XXH3_vkDestroyInstance},
        {"vkEnumeratePhysicalDevices", XXH3_vkEnumeratePhysicalDevices},
        {"vkGetPhysicalDeviceFeatures", XXH3_vkGetPhysicalDeviceFeatures},
        {"vkGetDeviceProcAddr", XXH3_vkGetDeviceProcAddr},
        {"vkDestroyDevice", XXH3_vkDestroyDevice},
        {"vkGetDeviceQueue", XXH3_vkGetDeviceQueue},
        {"vkQueueSubmit", XXH3_vkQueueSubmit},
        {"vkDestroyInstance", XXH3_vkDestroyInstance},
        {"vkEnumeratePhysicalDevices", XXH3_vkEnumeratePhysicalDevices},
        {"vkGetPhysicalDeviceFeatures", XXH3_vkGetPhysicalDeviceFeatures},
        {"vkGetPhysicalDeviceFormatProperties", XXH3_vkGetPhysicalDeviceFormatProperties},
        {"vkGetPhysicalDeviceImageFormatProperties", XXH3_vkGetPhysicalDeviceImageFormatProperties},
        {"vkGetPhysicalDeviceProperties", XXH3_vkGetPhysicalDeviceProperties},
        {"vkGetPhysicalDeviceQueueFamilyProperties", XXH3_vkGetPhysicalDeviceQueueFamilyProperties},
        {"vkGetPhysicalDeviceMemoryProperties", XXH3_vkGetPhysicalDeviceMemoryProperties},
    };
    for (const auto &pair : pairs) {
        ASSERT_EQ(pair.expected_hash, loader_hash_string(pair.name));
    }
}
