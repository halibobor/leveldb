#include <cassert>
#include <iostream>
#include <string>
#include <chrono>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

int main() {
  leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  options.paranoid_checks = true;
  options.block_size = 4 * 1024;
  options.write_buffer_size = 32 * 1024 * 1024;
  options.max_open_files = 1000;
  // 打开一个leveldb数据库
  std::time_t s = std::time(0);  // t is an integer type
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/leveldb/account", &db);
  assert(status.ok());
  std::time_t e = std::time(0);  // t is an integer type
  std::cout << e-s << " seconds for open \n";
  int read_records = 0;
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    read_records++;
  }
  assert(it->status().ok());  // Check for any errors found during the scan
  delete it;
  /*   assert(it->status().ok()); */ // Check for any errors found during the scan
   std::time_t ee = std::time(0);  // t is an integer type
   std::cout << ee-e << " seconds for Iterator \n";
   std::cout << read_records << " records....  \n";
   std::string val;
  bool is_ok = db->GetProperty("leveldb.approximate-memory-usage", &val);
  std::cout << is_ok << " is_ok \n";
  int mem_usage = std::stoi(val);
  std::cout << mem_usage << " mem_usage \n";
  delete db;

  leveldb::WriteBatch batch, batch2;
  size_t empty_size = batch.ApproximateSize();

  batch.Put(leveldb::Slice("foo"), leveldb::Slice("bar"));
  size_t one_key_size = batch.ApproximateSize();
  std::cout << empty_size << " empty_size....  \n";
  std::cout << one_key_size << " one_key_size....  \n";

  batch.Put(leveldb::Slice("baz"), leveldb::Slice("boo"));
  size_t two_keys_size = batch.ApproximateSize();
  std::cout << two_keys_size << " two_keys_size....  \n";

  batch.Delete(leveldb::Slice("box"));
  size_t post_delete_size = batch.ApproximateSize();
  std::cout << post_delete_size << " post_delete_size....  \n";

  batch2.Append(&batch);
  std::cout << batch2.ApproximateSize() << " batch2_size....  \n";
  batch.Clear();
  std::cout << batch.ApproximateSize() << " batch_size....  \n";
  batch.Append(&batch2);
  batch.Append(&batch2);
  std::cout << batch.ApproximateSize() << " batch_size....  \n";

  return 0;
}
