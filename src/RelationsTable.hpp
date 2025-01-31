#ifndef BASECLASSTABLE_HPP
#define BASECLASSTABLE_HPP
#include "sqlite3ext.h"
#include "VirtualTable.hpp"
#include "Service.grpc.pb.h"

enum RelationKind {
  BaseOf,
  OverriddenBy
};

class RelationsTable : public VirtualTable {
  std::unique_ptr<clang::clangd::remote::v1::SymbolIndex::Stub> m_stub;
  RelationKind m_kind;

public:
  RelationsTable(sqlite3* db, std::unique_ptr<clang::clangd::remote::v1::SymbolIndex::Stub> stub, RelationKind kind);

  virtual int BestIndex(sqlite3_index_info* info) override;
  virtual std::unique_ptr<VirtualTableCursor> Open() override;
  virtual int FindFunction(int nArg, const std::string& name, void (**pxFunc)(sqlite3_context*,int,sqlite3_value**), void **ppArg) override;
  virtual int Disconnect() override;
  virtual int Destroy() override;
};

#endif