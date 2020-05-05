//---------------------------------------------------------------------------//
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_BLOCK_DECRYPT_HPP
#define CRYPTO3_BLOCK_DECRYPT_HPP

#include <nil/crypto3/block/cipher_value.hpp>
#include <nil/crypto3/block/cipher_state.hpp>
#include <nil/crypto3/block/algorithm/encrypt.hpp>

namespace nil {
    namespace crypto3 {

        template<typename BlockCipher>
        using decryption_policy = typename block::modes::isomorphic<BlockCipher, nop_padding>::decryption_policy;
        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam BlockCipher
         * @tparam InputIterator
         * @tparam KeyIterator
         * @tparam OutputIterator
         *
         * @param first
         * @param last
         * @param key_first
         * @param key_last
         * @param out
         *
         * @return
         */
        template<typename BlockCipher, typename InputIterator, typename KeyIterator, typename OutputIterator>
        OutputIterator decrypt(InputIterator first, InputIterator last, KeyIterator key_first, KeyIterator key_last,
                               OutputIterator out) {

            typedef typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type DecryptionMode;
            typedef typename block::accumulator_set<DecryptionMode> CipherAccumulator;

            typedef block::detail::value_cipher_impl<CipherAccumulator> StreamDecrypterImpl;
            typedef block::detail::itr_cipher_impl<StreamDecrypterImpl, OutputIterator> DecrypterImpl;

            return DecrypterImpl(first, last, std::move(out), CipherAccumulator(DecryptionMode(BlockCipher(key_first, key_last))));
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam BlockCipher
         * @tparam InputIterator
         * @tparam OutputAccumulator
         *
         * @param first
         * @param last
         * @param out
         *
         * @return
         */
        template<
            typename BlockCipher, typename InputIterator,
            typename OutputAccumulator = typename block::accumulator_set<typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type>>
        OutputAccumulator &decrypt(InputIterator first, InputIterator last, OutputAccumulator &acc) {

            typedef block::detail::ref_cipher_impl<OutputAccumulator> StreamDecrypterImpl;
            typedef block::detail::range_cipher_impl<StreamDecrypterImpl> DecrypterImpl;

            return DecrypterImpl(first, last, acc);
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam BlockCipher
         * @tparam SinglePassRange
         * @tparam OutputAccumulator
         *
         * @param r
         * @param acc
         *
         * @return
         */
        template<
            typename BlockCipher, typename SinglePassRange,
            typename OutputAccumulator = typename block::accumulator_set<typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type>>
        OutputAccumulator &decrypt(const SinglePassRange &r, OutputAccumulator &acc) {

            typedef block::detail::ref_cipher_impl<OutputAccumulator> StreamDecrypterImpl;
            typedef block::detail::range_cipher_impl<StreamDecrypterImpl> DecrypterImpl;

            return DecrypterImpl(r, acc);
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam BlockCipher
         * @tparam InputIterator
         * @tparam KeyIterator
         * @tparam CipherAccumulator
         *
         * @param first
         * @param last
         * @param key_first
         * @param key_last
         *
         * @return
         */
        template<
            typename BlockCipher, typename InputIterator, typename KeyIterator,
            typename CipherAccumulator = typename block::accumulator_set<typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type>>
        block::detail::range_cipher_impl<block::detail::value_cipher_impl<CipherAccumulator>>
            decrypt(InputIterator first, InputIterator last, KeyIterator key_first, KeyIterator key_last) {

            typedef typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type DecryptionMode;

            typedef block::detail::value_cipher_impl<CipherAccumulator> StreamDecrypterImpl;
            typedef block::detail::range_cipher_impl<StreamDecrypterImpl> DecrypterImpl;

            return DecrypterImpl(first, last, CipherAccumulator(DecryptionMode(BlockCipher(key_first, key_last))));
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam BlockCipher
         * @tparam SinglePassRange
         * @tparam KeyRange
         * @tparam OutputIterator
         *
         * @param rng
         * @param key
         * @param out
         *
         * @return
         */
        template<typename BlockCipher, typename SinglePassRange, typename KeyRange, typename OutputIterator>
        OutputIterator decrypt(const SinglePassRange &rng, const KeyRange &key, OutputIterator out) {

            typedef typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type DecryptionMode;
            typedef typename block::accumulator_set<DecryptionMode> CipherAccumulator;

            typedef block::detail::value_cipher_impl<CipherAccumulator> StreamDecrypterImpl;
            typedef block::detail::itr_cipher_impl<StreamDecrypterImpl, OutputIterator> DecrypterImpl;

            return DecrypterImpl(rng, std::move(out), CipherAccumulator(DecryptionMode(BlockCipher(key))));
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam BlockCipher
         * @tparam SinglePassRange
         * @tparam KeyRange
         * @tparam CipherAccumulator
         *
         * @param r
         * @param key
         *
         * @return
         */
        template<
            typename BlockCipher, typename SinglePassRange, typename KeyRange,
            typename CipherAccumulator = typename block::accumulator_set<typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type>>
        block::detail::range_cipher_impl<block::detail::value_cipher_impl<CipherAccumulator>>
            decrypt(const SinglePassRange &r, const KeyRange &key) {

            typedef typename block::modes::isomorphic < BlockCipher,
                                            nop_padding>::template bind <decryption_policy<BlockCipher>>::type DecryptionMode;

            typedef block::detail::value_cipher_impl<CipherAccumulator> StreamDecrypterImpl;
            typedef block::detail::range_cipher_impl<StreamDecrypterImpl> DecrypterImpl;

            return DecrypterImpl(r, CipherAccumulator(DecryptionMode(BlockCipher(key))));
        }
    }    // namespace crypto3
}    // namespace nil

#endif    // include guard