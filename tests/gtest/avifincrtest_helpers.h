// Copyright 2022 Google LLC
// SPDX-License-Identifier: BSD-2-Clause

#ifndef LIBAVIF_TESTS_AVIFINCRTEST_HELPERS_H_
#define LIBAVIF_TESTS_AVIFINCRTEST_HELPERS_H_

#include <cstdint>

#include "avif/avif.h"

namespace libavif {
namespace testutil {

// Encodes a portion of the image to be decoded incrementally.
void EncodeRectAsIncremental(const avifImage& image, uint32_t width,
                             uint32_t height, bool create_alpha_if_none,
                             bool flat_cells, avifRWData* output,
                             uint32_t* cell_width, uint32_t* cell_height);

// Decodes incrementally the encoded_avif and compares the pixels with the given
// reference. If is_persistent is true, the input encoded_avif is considered as
// accessible during the whole decoding. If give_size_hint is true, the whole
// encoded_avif size is given as a hint to the decoder. use_nth_image_api
// describes whether the NthImage or NextImage decoder API will be used. The
// cell_height of all planes of the encoded_avif is given to estimate the
// incremental granularity. enable_fine_incremental_check checks that sample
// rows are gradually output when feeding more and more input bytes to the
// decoder.
void DecodeIncrementally(const avifRWData& encoded_avif, avifDecoder* decoder,
                         bool is_persistent, bool give_size_hint,
                         bool use_nth_image_api, const avifImage& reference,
                         uint32_t cell_height,
                         bool enable_fine_incremental_check = false,
                         bool expect_whole_file_read = true);

// Calls DecodeIncrementally() with the reference being a regular decoding of
// encoded_avif.
void DecodeNonIncrementallyAndIncrementally(
    const avifRWData& encoded_avif, avifDecoder* decoder, bool is_persistent,
    bool give_size_hint, bool use_nth_image_api, uint32_t cell_height,
    bool enable_fine_incremental_check = false,
    bool expect_whole_file_read = true);

}  // namespace testutil
}  // namespace libavif

#endif  // LIBAVIF_TESTS_AVIFINCRTEST_HELPERS_H_
