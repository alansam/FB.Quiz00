#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <numeric>
#include <functional>
#include <cctype>

class Question {
public:
  Question(std::string const & ask,
           std::string const & opt_a,
           std::string const & opt_b,
           std::string const & opt_c,
           std::string const & opt_d,
           int const ans,
           int const score)
  : ask_   { ask },
    opts_  { opt_a, opt_b, opt_c, opt_d },
    ans_   { ans },
    score_ { score } {}
  Question() = delete;
  Question(Question const &) = default;
  Question(Question &&) = default;
  Question & operator=(Question const &) = default;
  Question & operator=(Question &&) = default;
  ~Question() = default;

  auto ask(void) const {
    return ask_;
  }
  auto ask(std::string const & ask) -> std::string {
    return (ask_ = ask);
  }
  auto opts(void) const {
    return opts_;
  }
  auto opts(std::array<std::string, 4> const & opts)
    -> std::array<std::string, 4> {
    opts_[0] = opts[0];
    opts_[1] = opts[1];
    opts_[2] = opts[2];
    opts_[3] = opts[3];
    return opts_;
  }
  auto ans(void) const {
    return ans_;
  }
  auto ans(int ans) {
    ans_ = ans;
    return (ans_ = ans);
  }
  auto score(void) const {
    return score_;
  }
auto score(int score) {
  return (score_ = score);
}

  int test(void) const {
    std::cout << ask_ << '\n';
    std::cout << ' ' << opts_[0] << '\n';
    std::cout << ' ' << opts_[1] << '\n';
    std::cout << ' ' << opts_[2] << '\n';
    std::cout << ' ' << opts_[3] << '\n';
    auto score = 0;
    auto ans = 0;
    std::cout << "your choice [1 thru 4]:\n";
    std::cin >> ans;
    if (ans == ans_) {
      std::cout << "correct.\n";
      score = score_;
    }
    else {
      std::cout << "incorrect.\n";
    }

    return score;
  }

friend
  std::ostream & operator<<(std::ostream & os, Question const & that) {
    os << that.ask_     << ' '
       << that.opts_[0] << ' '
       << that.opts_[1] << ' '
       << that.opts_[2] << ' '
       << that.opts_[3] << ' '
       << that.ans_     << ' '
       << that.score_;
    return os;
  }

private:
  std::string ask_;
  std::array<std::string, 4> opts_;
  int ans_;
  int score_;
};

/*
 *  MARK:  load_quiz()
 */
static
auto load_quiz(void) {
  auto quiz = std::vector<Question> {
    Question("Hello World!",
             "1. Question 1?",
             "2. Question 2?",
             "3. Question 3?",
             "4. Question 4?",
             3,
             10),
    Question("You Again?",
             "1. Question 1?",
             "2. Question 2?",
             "3. Question 3?",
             "4. Question 4?",
             2,
             15),
      Question("If you Must!",
             "1. Question 1?",
             "2. Question 2?",
             "3. Question 3?",
             "4. Question 4?",
             1,
             17),
  };

  return quiz;
}

/*
 *  MARK:  main()
 */
int main() {
  auto quiz { load_quiz() };

  auto max_score = std::accumulate(quiz.cbegin(),
                                   quiz.cend(),
                                   0,
    [](auto sum, auto const & qz) {
      return sum + qz.score();
    });

  std::cout << "max score: " << max_score << '\n';
  std::cout.put('\n');

  auto total = 0;
  for (auto const & qq : quiz) {
    std::cout << qq << '\n';
    total += qq.test();
    std::cout << "running total: " << total << '\n';
  }
  std::cout << "total score: " << total << '\n';

  auto pct = 1.0 * total / max_score * 100.0;
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "grade: " << pct << '%' << '\n';

  return 0;
}
