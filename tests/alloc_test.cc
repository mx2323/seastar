/*
 * This file is open source software, licensed to you under the terms
 * of the Apache License, Version 2.0 (the "License").  See the NOTICE file
 * distributed with this work for additional information regarding copyright
 * ownership.  You may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
/*
 * Copyright (C) 2015 Cloudius Systems, Ltd.
 */

#include "tests/test-utils.hh"
#include "core/memory.hh"
#include <thread>

SEASTAR_TEST_CASE(alloc_almost_all_and_realloc_it_with_a_smaller_size) {
#ifndef DEFAULT_ALLOCATOR
    auto all = memory::stats().total_memory();
    auto reserve = size_t(0.02 * all);
    auto to_alloc = all - (reserve + (10 << 20));
    auto obj = malloc(to_alloc);
    BOOST_REQUIRE(obj != nullptr);
    auto obj2 = realloc(obj, to_alloc - (1 << 20));
    BOOST_REQUIRE(obj == obj2);
    free(obj2);
#endif
    return make_ready_future<>();
}

std::thread * foo = nullptr;
SEASTAR_TEST_CASE(third_party_allocator) {
#ifndef DEFAULT_ALLOCATOR
	std::cout << "third party allocator test" << std::endl;
    auto *a = malloc(4);
    auto *b = realloc(nullptr, 4);
    std::thread foo([](){
        auto *i = malloc(4);
        auto *j = realloc(nullptr, 4);
        assert(!memory::is_seastar_memory(i));
        assert(!memory::is_seastar_memory(j));
		free(i);
		free(j);
	});
    assert(memory::is_seastar_memory(a));
    assert(memory::is_seastar_memory(b));
    free(a);
    free(b);
	foo.join();
#else
    auto *i = malloc(4);
    assert(!memory::is_seastar_memory(i));
    free(i);
#endif
	return make_ready_future<>();
}
