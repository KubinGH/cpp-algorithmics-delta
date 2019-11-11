import Data.Int
import Data.List
import Control.Monad

data MSP a = MSP {
    pref::a,
    suff::a,
    best::a,
    sumv::a
}
monoMSP x = let y = max x 0 in MSP y y y x

combineMSP lhs rhs = MSP
    (max (pref lhs) (sumv lhs + pref rhs))
    (max (suff rhs) (suff lhs + sumv rhs))
    (max (suff lhs + pref rhs) (max (best lhs) (best rhs)))
    (sumv lhs + sumv rhs)


data SegmentTree a
    = Leaf a
    | Node (SegmentTree a) a (SegmentTree a)
rootValue tree = case tree of
    Leaf v -> v
    Node _ v _ -> v
joinTrees f left right = Node left (f (rootValue left) (rootValue right)) right


makeFilledSegmentTree v f h =
    let
        child = makeFilledSegmentTree v f (h-1)
    in
        if h <= 0 then
            Leaf v
        else
            joinTrees f child child

set v i f tree l r = case tree of
    Leaf _ -> Leaf v
    Node left _ right -> let m = (l+r) `div` 2 in
        if i <= m then
            let left' = set v i f left l m
            in joinTrees f left' right
        else
            let right' = set v i f right (m+1) r
            in joinTrees f left right'

get i tree l r = case tree of
    Leaf v -> v
    Node left _ right -> let m = (l+r) `div` 2 in
        if i <= m then
            get i left l m
        else
            get i right (m+1) r


floorLog2 n = if n == 1 then 0 else 1 + (floorLog2 (n `div` 2))
ceilLog2 n = floorLog2 (2*n-1)

intToInt64 :: Int -> Int64
intToInt64 = fromIntegral


answers' n k d queries tree = if null queries then [] else
    let
        (curr : queries') = queries
        [r', x] = curr
        r = r' - 1
        p = sumv (get r tree 0 (n-1))
        q = p + (intToInt64 x)
        tree' = set (monoMSP q) r combineMSP tree 0 (n-1)
        rest = answers' n k d queries' tree'
        val = best (rootValue tree')
    in
        (if val > d*k then "NIE" else "TAK") : rest

answers n k d queries =
    let
        h = max 1 (ceilLog2 n)
    in
        answers' (2^h) k d queries (makeFilledSegmentTree (monoMSP (-k)) combineMSP h)

main = do
    paramStr <- getLine
    let [n, m, k, d] = map read $ words paramStr
    queriesStr <- replicateM m getLine
    let queries = map (\l -> map read $ words l :: [Int]) queriesStr
    putStrLn (intercalate "\n" (answers n (intToInt64 k) (intToInt64 d) queries))
