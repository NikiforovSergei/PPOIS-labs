#import "PostMachine/PostMachine.h"

using namespace postMachine;
int main() {
  machine Post;

  Post.flaunch("../Tests/test2.txt", true);
  return 0;
}
