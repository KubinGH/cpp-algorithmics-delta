
struct interval_tree
{
    array<uint32_t, TSIZE> values;
    array<array<uint32_t, 3>, TSIZE> leaf_values, to_add;
    void set_value(uint32_t i, uint32_t value, uint32_t k = 0)
    {
        i += TSIZE/2;
        leaf_values[i][k] = value;
        values[i] += value;
        i /= 2;
        values[i] = max(leaf_values[i][0] + leaf_values[i][1] + leaf_values[i][2],
                        leaf_values[i^1][0] + leaf_values[i^1][1] + leaf_values[i^1][2]);
        while(i > 1)
            i /= 2, values[i] = max(values[2*i], values[2*i+1]);
    }
    uint32_t add_value(uint32_t i, uint32_t tbegin, uint32_t tend,
                       uint32_t sbegin, uint32_t send, uint32_t value, uint32_t k)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_add[i][k] += value;
            return value;
        }
        else
        {
            uint32_t a, b;
            a = add_value(2*i, tbegin, (tbegin+tend)/2, sbegin, send, value, k);
            b = add_value(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send, value, k);
            values[i] += a + b;
            return a + b;
        }
    }
    uint32_t add_value(uint32_t sbegin, uint32_t send, uint32_t value, uint32_t k)
    {
        return add_value(1, 0, TSIZE/2-1, sbegin, send, value, k);
    }

};
