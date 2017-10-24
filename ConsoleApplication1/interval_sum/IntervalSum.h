#pragma once

#include <vector>

namespace
{

struct Node
{
    Node()
        : lson{ -1 }, rson{ -1 }
        , sum1{ 0 }, sum2{ 0 }, sum3{ 0 }
        , l{ -1 }, r{ -1 }
        , d1{ 0 }, d2{ 0 }, d3{ 0 }
    {}

    int lson, rson;
    int sum1, sum2, sum3;
    int l, r;
    int d1, d2, d3;
};

class IntervalSum
{
public: 
    IntervalSum(const std::vector<int>& data);

    void Add(int l, int r, int v);
    int Solve(int l, int r) const;

private:
    int BuildTree(int l, int r);
    int GetSum(int root, int l, int r) const;

    const std::vector<int>& m_data;
    std::vector<Node> m_nodes;
};

IntervalSum::IntervalSum(const std::vector<int>& data)
    : m_data{ data }
{
    m_nodes.clear();
    m_nodes.reserve(data.size() * 4);
    
    BuildTree(0, data.size() - 1);
}

void IntervalSum::Add(const int l, const int r, const int v)
{

}

int IntervalSum::Solve(const int l, const int r) const
{
    return GetSum(0, l, r);
}

int IntervalSum::BuildTree(const int l, const int r)
{
    int currIndex = m_nodes.size();

    m_nodes.push_back({});
    m_nodes[currIndex].l = l;
    m_nodes[currIndex].r = r;

    if (l == r)
    {
        m_nodes[currIndex].sum1 = m_data[l];
        m_nodes[currIndex].sum2 = m_data[l] * m_nodes[currIndex].sum1;
        m_nodes[currIndex].sum3 = m_data[l] * m_nodes[currIndex].sum2;
    }
    else
    {
        int m = (l + r) / 2;

        int lRoot = BuildTree(l, m);
        int rRoot = BuildTree(m + 1, r);

        m_nodes[currIndex].lson = lRoot;
        m_nodes[currIndex].rson = rRoot;
        m_nodes[currIndex].sum1 = m_nodes[lRoot].sum1 + m_nodes[rRoot].sum1;
        m_nodes[currIndex].sum2 = m_nodes[lRoot].sum2 + m_nodes[rRoot].sum2;
        m_nodes[currIndex].sum3 = m_nodes[lRoot].sum3 + m_nodes[rRoot].sum3;
    }

    return currIndex;
}

int IntervalSum::GetSum(const int root, const int l, const int r) const
{
    const auto& node = m_nodes[root];
    int taggedSum = node.sum3 * (r - l + 1);

    if (l == node.l && r == node.r)
    {
        return node.sum3 + taggedSum;
    }
    else
    {
        int m = (node.l + node.r) / 2;
        int lSum{ 0 }, rSum{ 0 };
        
        if (l <= m)
        {
            lSum = GetSum(node.lson, l, m);
        }

        if (r > m)
        {
            rSum = GetSum(node.rson, m + 1, r);
        }

        return lSum + rSum + taggedSum;
    }
}

}