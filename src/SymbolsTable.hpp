#ifndef SYMBOLSTABLE_HPP
#define SYMBOLSTABLE_HPP
#include "sqlite3ext.h"
#include "VirtualTable.hpp"
#include "Service.grpc.pb.h"

class SymbolsTable : public VirtualTable {
  std::unique_ptr<clang::clangd::remote::v1::SymbolIndex::Stub> m_stub;

public:
  SymbolsTable(sqlite3* db, std::unique_ptr<clang::clangd::remote::v1::SymbolIndex::Stub> stub);

  virtual int BestIndex(sqlite3_index_info* info) override;
  virtual std::unique_ptr<VirtualTableCursor> Open() override;
  virtual int FindFunction(int nArg, const std::string& name, void (**pxFunc)(sqlite3_context*,int,sqlite3_value**), void **ppArg) override;
  virtual int Disconnect() override;
  virtual int Destroy() override;
};

#endif