//---------------------------------------------------------------------------//
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#define BOOST_TEST_MODULE noekeon_cipher_test

#include <iostream>
#include <unordered_map>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <nil/crypto3/block/algorithm/encrypt.hpp>
#include <nil/crypto3/block/algorithm/decrypt.hpp>

#include <nil/crypto3/block/aria.hpp>

using namespace nil::crypto3;

BOOST_AUTO_TEST_SUITE(aria_test_suite)

BOOST_AUTO_TEST_CASE(aria_1) {

    std::vector<char> input = {'\x00', '\x11', '\x22', '\x33', '\x44', '\x55', '\x66', '\x77', 
                                '\x88', '\x99', '\xaa', '\xbb', '\xcc', '\xdd', '\xee', '\xff'};
    std::vector<char> key = {'\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', 
                            '\x08', '\x09', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f'};

    std::string out = encrypt<block::aria<128>>(input, key);

    BOOST_CHECK_EQUAL(out, "d718fbd6ab644c739da95f3be6451778");
}

BOOST_AUTO_TEST_SUITE_END()     