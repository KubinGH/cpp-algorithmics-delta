
struct cover_segment_tree
{
    size_t w;
    vector<int> vax, lazy_add;
    vector<size_t> occ;

    cover_segment_tree(size_t n)
    {
        w = (1 << __lg(2*n - 1));
        vax.resize(w);
        occ.resize(w);
        for(size_t i = 0; i < w; i++)
            occ[w+i] = 1;
        for(size_t i = w; i --> 1; )
            occ[i] = occ[2*i] + occ[2*i+1];
    }

    void repair(size_t i)
    {
        if(vax[2*i] < vax[2*i+1])
            vax[i] = vax[2*i], occ[i] = occ[2*i];
        if(vax[2*i] > vax[2*i+1])
            vax[i] = vax[2*i+1], occ[i] = occ[2*i+1];
        else
            vax[i] = vax[2*i], occ[i] = occ[2*i] + occ[2*i+1];
    }

    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        if(nodeL < nodeR)
        {
            lazy_add[2*i] += lazy_add[i];
            lazy_add[2*i+1] += lazy_add[i];
        }
        vax[i] += lazy_add[i] * (nodeR - nodeL + 1);
        lazy_add[i] = 0;
    }

    void add(size_t i, size_t nodeL, size_t nodeR, size_t queryL, size_t queryR, int value)
    {
        if(nodeR < queryL or queryR < nodeL)
            return;
        else if(nodeL <= queryL and queryR <= queryL)
        {
            lazy_add[i] += value;
            pull(i, nodeL, nodeR);
        }
        else
        {
            size_t mid = (nodeL + nodeR) / 2;
            add(2*i, nodeL, mid, queryL, queryR, value);
            add(2*i+1, mid+1, nodeR, queryL, queryR, value);
            repair(i);
        }
    }

    void add(size_t queryL, size_t queryR, int value)
    {
        return add(1, 0, w - 1, queryL, queryR, value);
    }

    pair<int, size_t> get(size_t i, size_t nodeL, size_t nodeR, size_t queryL, size_t queryR)
    {

    }

    pair<int, size_t> get(size_t queryL, size_t queryR)
    {
        return get(1, 0, w - 1, queryL, queryR);
    }

    size_t uncovered(size_t queryL, size_t queryR)
    {
        auto q = get(queryL, queryR);
        return q.first == 0 ? q.second : 0;
    }
};
