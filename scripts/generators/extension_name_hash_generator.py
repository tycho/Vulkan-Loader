#!/usr/bin/python3 -i
#
# Copyright (c) 2015-2022 The Khronos Group Inc.
# Copyright (c) 2015-2022 Valve Corporation
# Copyright (c) 2015-2022 LunarG, Inc.
# Copyright (c) 2015-2017 Google Inc.
# Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# Copyright (c) 2023-2023 RasterGrid Kft.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: Mark Young <marky@lunarg.com>
# Author: Mark Lobodzinski <mark@lunarg.com>
# Author: Charles Giessen <charles@lunarg.com>

import re
import os
import sys
from base_generator import BaseGenerator
from vulkan_object import Version
from xxhash import xxh3_64_hexdigest


class ExtensionNameHashGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

        self.extension_names = []

    def generate(self):
        self.extension_names = [x.name for x in self.vk.extensions.values()]

        out = []
        self.add_preamble(out)

        self.print_vk_extension_name_hashes(out)

        out.append('// clang-format on')

        self.write(''.join(out))

    def add_preamble(self, out):
        out.append(f'''// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See {os.path.basename(__file__)} for modifications

/*
 * Copyright (c) 2015-2025 The Khronos Group Inc.
 * Copyright (c) 2015-2025 Valve Corporation
 * Copyright (c) 2015-2025 LunarG, Inc.
 * Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * Copyright (c) 2023-2023 RasterGrid Kft.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Mark Young <marky@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

#define XXH_INLINE_ALL
#include <xxhash.h>

// clang-format off
''')

    def print_vk_extension_name_hashes(self, out):
        seen_hashes = {}
        for name in sorted(self.extension_names):
            nameHash = xxh3_64_hexdigest(name.encode('utf-8'))
            if nameHash in seen_hashes:
                sys.stderr.write("Hash collision for {} ('{}' and '{}')\n".format(nameHash, name, seen_hashes[nameHash]))
                sys.exit(1)
            seen_hashes[nameHash] = name
            out.append(f'#define XXH3_{name} 0x{nameHash}ULL\n')
