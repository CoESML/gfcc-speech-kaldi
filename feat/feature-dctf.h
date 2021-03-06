// feat/feature-dctf.h


#ifndef KALDI_FEAT_FEATURE_DCTF_H_
#define KALDI_FEAT_FEATURE_DCTF_H_

#include "feat/feature-functions.h"
#include "feat/feature-window.h"

namespace kaldi {
/// @addtogroup  feat FeatureExtraction
/// @{


/// DctfOptions contains basic options for computing DCTF features
/// It only includes things that can be done in a "stateless" way, i.e.
/// it does not include energy max-normalization.
/// It does not include delta computation.
struct DctfOptions {
  FrameExtractionOptions frame_opts;
  int32 num_bins;  // e.g. 64: num DCTF bins, counting zero.
  int32 num_ceps;  // e.g. 23: num GF cepstral coeffs, counting zero.

  void Register(ParseOptions *po) {
    frame_opts.Register(po);
  }
};

/// Class for computing DCTF features; see \ref feat_dctf for more information.
class Dctf {
 public:
  Dctf(const DctfOptions &opts);
  ~Dctf();

  int32 Dim() { return opts_.num_ceps; }

  /// Will throw exception on failure (e.g. if file too short for even one
  /// frame).  The output "wave_remainder" is the last frame or two of the
  /// waveform that it would be necessary to include in the next call to Compute
  /// for the same utterance.  It is not exactly the un-processed part (it may
  /// have been partly processed), it's the start of the next window that we
  /// have not already processed.  Will throw exception on failure (e.g. if file
  /// too short for even one frame).
  void Compute(const VectorBase<BaseFloat> &wave,
               Matrix<BaseFloat> *output,
               Vector<BaseFloat> *wave_remainder = NULL);

 private:
  DctfOptions opts_;
  Matrix<BaseFloat> dct_matrix_;  // matrix we left-multiply by to perform DCT.
  FeatureWindowFunction feature_window_function_;
  KALDI_DISALLOW_COPY_AND_ASSIGN(Dctf);
};


/// @} End of "addtogroup feat"
}  // namespace kaldi


#endif  // KALDI_FEAT_FEATURE_DCTF_H_
