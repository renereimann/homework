#include "unique_id.hpp"

// constructor
unique_id::unique_id(): id_(++count_), id_t_(time_), id_of_process_(process_) { };

// printing
std::ostream& operator <<(std::ostream& os, const unique_id& id){
    std::time_t ttp = std::chrono::system_clock::to_time_t(id.id_t_);
    return os << "ID: " << id.id_ << " generated by process " << id.id_of_process_ << " started at " << std::ctime(&ttp);
}

// comparison
bool operator==(const unique_id& lhs, const unique_id& rhs) { 
    return    (lhs.id_ == rhs.id_) 
           && (lhs.id_of_process_ == rhs.id_of_process_) 
           && (lhs.id_t_ == rhs.id_t_); 
};

bool operator!=(const unique_id& lhs, const unique_id& rhs){
    return !(lhs == rhs);
};

// initial initialization
// has to be in the source file, not in the header, because otherwise 
// initialization may happen multiple times, leading to linking errors

unsigned unique_id::count_ = 0;
int unique_id::process_ = ::getpid();
std::chrono::_V2::system_clock::time_point unique_id::time_ = std::chrono::system_clock::now();

// test unique_id
TEST(UniqueIdTest, construct) {
  unique_id id1;
  unique_id id2;
  unique_id id3(id2);
  std::cout << id1 << std::endl;
  std::cout << id2 << std::endl;
  std::cout << id3 << std::endl;
  EXPECT_EQ(id1, id1);
  EXPECT_EQ(id2, id2);
  EXPECT_EQ(id3, id3);
  EXPECT_NE(id1, id2);
  EXPECT_EQ(id2, id3);
  EXPECT_TRUE(id2 == id2);
  EXPECT_TRUE(id1 != id2);
  EXPECT_FALSE(id1 == id2);
  EXPECT_TRUE(id2 == id3);
}