#ifndef NMTKIT_CORPUS_H_
#define NMTKIT_CORPUS_H_

#include <istream>
#include <string>
#include <vector>
#include <nmtkit/basic_types.h>
#include <nmtkit/vocabulary.h>

namespace nmtkit {

class Corpus {
  Corpus() = delete;
  Corpus(const Corpus &) = delete;
  Corpus(Corpus &&) = delete;
  Corpus & operator=(const Corpus &) = delete;
  Corpus & operator=(Corpus &&) = delete;

public:
  // Reads one line from the input stream.
  //
  // Arguments:
  //   is: Target input stream.
  //   line: Placeholder to store new string. Old data will be deleted before
  //         storing the new value.
  //
  // Returns:
  //   true if reading completed successfully, false otherwise (e.g. EOF).
  static bool readLine(std::istream * is, std::string * line);

  // Reads one line from the input stream.
  //
  // Arguments:
  //   vocab: Vocabulary object to be used to convert words into word IDs.
  //   is: Target input stream.
  //   words: Placeholder to store new words. Old data will be deleted
  //          automatically before storing new samples.
  //
  // Returns:
  //   true if reading completed successfully, false otherwise (e.g. EOF).
  static bool readTokens(
      const Vocabulary & vocab,
      std::istream * is,
      std::vector<unsigned> * word_ids);

  // Loads all samples in the tokenized corpus.
  //
  // Arguments:
  //   filepath: Location of the corpus file.
  //   vocab: Vocabulary object for the corpus language.
  //   result: Placeholder to store new samples. Old data will be deleted
  //           automatically before storing new samples.
  static void loadSingleSentences(
      const std::string & filepath,
      const Vocabulary & vocab,
      std::vector<std::vector<unsigned>> * result);

  // Loads tokenized parallel corpus.
  //
  // Arguments:
  //   src_filepath: Location of the source corpus file.
  //   trg_filepath: Location of the target corpus file.
  //   src_vocab: Vocabulary object for the source language.
  //   trg_vocab: Vocabulary object for the target language.
  //   max_length: Maximum number of words in a sentence. Samples which exceeds
  //               this value will be skipped.
  //   max_length_ratio: Maximum ratio of lengths in source/target sentences.
  //                     Samples which exceeds this value will be skipped.
  //   src_result: Placeholder to store new source samples. Old data will be
  //               deleted automatically before storing new samples.
  //   trg_result: Placeholder to store new target samples. Old data will be
  //               deleted automatically before storing new samples.
  static void loadParallelSentences(
      const std::string & src_filepath,
      const std::string & trg_filepath,
      const Vocabulary & src_vocab,
      const Vocabulary & trg_vocab,
      unsigned max_length,
      float max_length_ratio,
      std::vector<std::vector<unsigned>> * src_result,
      std::vector<std::vector<unsigned>> * trg_result);

  // Loads tokenized parallel corpus directly to Sample objects.
  //
  // Arguments:
  //   src_filepath: Location of the source corpus file.
  //   trg_filepath: Location of the target corpus file.
  //   src_vocab: Vocabulary object for the source language.
  //   trg_vocab: Vocabulary object for the target language.
  //   max_length: Maximum number of words in a sentence. Samples which exceeds
  //               this value will be skipped.
  //   max_length_ratio: Maximum ratio of lengths in source/target sentences.
  //                     Samples which exceeds this value will be skipped.
  //   result: Placeholder to store new source/target samples. Old data will be
  //           deleted automatically before storing new samples.
  static void loadParallelSentences(
      const std::string & src_filepath,
      const std::string & trg_filepath,
      const Vocabulary & src_vocab,
      const Vocabulary & trg_vocab,
      unsigned max_length,
      float max_length_ratio,
      std::vector<Sample> * result);
};

}  // namespace nmtkit

#endif  // NMTKIT_CORPUS_H_
