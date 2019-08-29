trap exit INT
cat 6AeE978.tmp.log
sleep 0.033s
printf "\n\n[Exited with code $?]\n"
read -rsn1 -p "Press any key to continue . . ."
echo
