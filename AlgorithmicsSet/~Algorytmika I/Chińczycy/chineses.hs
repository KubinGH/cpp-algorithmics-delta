egcd 0 b = (b, 0, 1)
egcd a b = (d, x, y)
    where
        (d, x', y') = egcd (b `mod` a) a
        x = y' - (b `div` a) * x'
        y = x'

main = do
    paramStr <- getLine
    let [m1, m2, a1, a2] = map read $ words paramStr
    let (_, x, y) = egcd m1 m2
    print $ (m1 * x * (a2-a1) + a1) `mod` m1*m2 
