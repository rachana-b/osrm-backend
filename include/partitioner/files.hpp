#ifndef OSRM_PARTITIONER_SERILIZATION_HPP
#define OSRM_PARTITIONER_SERILIZATION_HPP

#include "customizer/edge_based_graph.hpp"

#include "partitioner/serialization.hpp"

#include "storage/io.hpp"

namespace osrm
{
namespace partitioner
{
namespace files
{

// reads .osrm.mldgr file
template <typename MultiLevelGraphT>
inline void readGraph(const boost::filesystem::path &path,
                      MultiLevelGraphT &graph,
                      std::uint32_t &connectivity_checksum)
{
    static_assert(std::is_same<customizer::MultiLevelEdgeBasedGraphView, MultiLevelGraphT>::value ||
                      std::is_same<customizer::MultiLevelEdgeBasedGraph, MultiLevelGraphT>::value,
                  "");

    storage::tar::FileReader reader{path, storage::tar::FileReader::VerifyFingerprint};

    serialization::read(reader, "/mld/multilevelgraph", graph, connectivity_checksum);
}

// writes .osrm.mldgr file
template <typename MultiLevelGraphT>
inline void writeGraph(const boost::filesystem::path &path,
                       const MultiLevelGraphT &graph,
                       const std::uint32_t connectivity_checksum)
{
    static_assert(std::is_same<customizer::MultiLevelEdgeBasedGraphView, MultiLevelGraphT>::value ||
                      std::is_same<customizer::MultiLevelEdgeBasedGraph, MultiLevelGraphT>::value,
                  "");

    storage::tar::FileWriter writer{path, storage::tar::FileWriter::GenerateFingerprint};

    serialization::write(writer, "/mld/multilevelgraph", graph, connectivity_checksum);
}

// read .osrm.partition file
template <typename MultiLevelPartitionT>
inline void readPartition(const boost::filesystem::path &path, MultiLevelPartitionT &mlp)
{
    static_assert(std::is_same<MultiLevelPartitionView, MultiLevelPartitionT>::value ||
                      std::is_same<MultiLevelPartition, MultiLevelPartitionT>::value,
                  "");

    const auto fingerprint = storage::tar::FileReader::VerifyFingerprint;
    storage::tar::FileReader reader{path, fingerprint};

    serialization::read(reader, "/mld/multilevelpartition", mlp);
}

// writes .osrm.partition file
template <typename MultiLevelPartitionT>
inline void writePartition(const boost::filesystem::path &path, const MultiLevelPartitionT &mlp)
{
    static_assert(std::is_same<MultiLevelPartitionView, MultiLevelPartitionT>::value ||
                      std::is_same<MultiLevelPartition, MultiLevelPartitionT>::value,
                  "");

    const auto fingerprint = storage::tar::FileWriter::GenerateFingerprint;
    storage::tar::FileWriter writer{path, fingerprint};

    serialization::write(writer, "/mld/multilevelpartition", mlp);
}

// reads .osrm.cells file
template <typename CellStorageT>
inline void readCells(const boost::filesystem::path &path, CellStorageT &storage)
{
    static_assert(std::is_same<CellStorageView, CellStorageT>::value ||
                      std::is_same<CellStorage, CellStorageT>::value,
                  "");

    const auto fingerprint = storage::tar::FileReader::VerifyFingerprint;
    storage::tar::FileReader reader{path, fingerprint};

    serialization::read(reader, "/mld/cellstorage", storage);
}

// writes .osrm.cells file
template <typename CellStorageT>
inline void writeCells(const boost::filesystem::path &path, CellStorageT &storage)
{
    static_assert(std::is_same<CellStorageView, CellStorageT>::value ||
                      std::is_same<CellStorage, CellStorageT>::value,
                  "");

    const auto fingerprint = storage::tar::FileWriter::GenerateFingerprint;
    storage::tar::FileWriter writer{path, fingerprint};

    serialization::write(writer, "/mld/cellstorage", storage);
}
}
}
}

#endif
