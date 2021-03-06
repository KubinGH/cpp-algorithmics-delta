#!/usr/bin/python

import sys, string

b64 = string.digits + string.ascii_uppercase + string.ascii_lowercase + '+/'

raw = ('0a0by0m3ch0ai4dwokat0a7ha2kte2urat5lbo0wiem6e0i1z3mfiteatr0u1zeAncjum4i0zeli6postol0a7rene1ie2y4scka3esor0a6trium5ugusta1ianie2ow5y5lus0a1ow6z0eby0m1s6baba2dz2l1ranka4dziej3o3on0a1owa1ej7wil4eda0c2e1zie0my2sz6lu2rnardyn0a8z2iada2la1e1y3c1ega1l1u2rze3zy3let4lask0u4iska1o3zej5o0daj3g0a1om1w0ie4u2i1ju2k0iem3u2l0u2m1ru2ska1i2two4wiem4ze3racia1e3k0lo3l1ma1e1y2t2on0i0a4wi3uchman5rza4y0c1l0a0by3by2e0m2i1o0by3y2m1s3cala1e0go2j2kiem4y0m4el0u2nturion7sarz4zar0a1em2owi3ze6ha0rtow2y4ca0c2e0sz3ial0a1bym3em6ec2ilo0n0a1ie6lopak2ca2iec6mura1y4oc0by2iaz4dzi0c1l0o5ry2wa3ryste1us0a5zotemis8zciciel0a7escijan0ami3ie1nem4omBwala3ila0mi3e1i3ycil3ta4yba1il5i0agle2nal2ela3ie3u2l0a1o3che1o1u3e0bie3zko4otka1i4sza1y4o0fnal4m1raz2ka1i3s1z2ubiculum8yrku4zarna1e1y3s0ach2mi3em2ie2ow2u3ci2ego0s3ka0c1ja0c3l3le2mu2sc0i0ej4to4lek2owiek0a1iem9olo3tery4ujac2e2l0a3y0li2m0s2ni0c1l3sta3tal3z4da0browski7c1j0e2l0a1ej1ka1o3i0bog5m0a1om2y2no2remnie5mo3wal2na1e0go3iej3o1ych6iabla1i5la0czego0z6tego5on0i0e4uga1i0e1m0i3o2zej5ni0a0ch5o0bra1e1odziej6y0m2ze1ynie2scy2ki0ch9yl3dal0a4kad2ola3tor0a5l0e2m0em2ow2u1y2piero4oki3rawdy6sc1tal3yc3tad2ychczas8wod4razki4odze3ga1e1i3uga1i0ch2e0go2j2m4zew0a3wi0ach7ucha1u3sza1e1y3ze1o1y3wa0dziescia8j1kroc5ie2och2r0u1ze4u2zialo3eci0e2ka1iem3o3dzic1niec7je2ki1uje4n1siec0iu6wczyna1e1y5ice1y2ecdziesiatDs0iaj4wna1e1y6e0konom5unice5welina7fala1e3elicja6lorentyna9olwarku6ntanny6rum3telu5ranc1kow7gabinecie3tu6dac1l4dy0by0m1s3m1z2zie0niegdzie8s1z5eist0a4rwazy5sto4inie4ladiatorow8uka1us5ebi1oko5os0em2no2ow2y2wa0mi3e1ie2y3upi1stwo7niew0u5o0dzin0a1e1y5r0aco3e1y1ze3sc0i0a1e3podarza8tow4ranice5ecji2yna4k0a3omada1e1y4zi3zecznie2oscAha0ndel2lu4slo4ejze3lunia5rbate4kulesa8istorie7onor0u4pfera5reszkow8rabi0a1e0go3na1y2o5umor5i0ch2da0c2z0ie4gnacego3y4rzysk0a7le0kroc4z3m0ie3naczej5na1e0go3i1y0ch2m0i4teres0a1ow2u7sc1tocie3tnie7z0abela1e1i5bie2y4ja0cek3k0a0s2by2i0ch2e0go0s3j0s2s2m0s2s2kolwiek7o0z2ze3l1m1n0kiel5snie5e0chac4den2li2na0k0ze4ego2j2i1o0czesnie8ym3ynie4zie4go0mosc5row2y3j1mu2neral0e6sli2t0em1s0my5zcze5zeli5owisza6utro3z0ci5kamien0ice1y7pelusz5itan4licy5rabele5ty3tz2zal0a3da1ego2j2y0m3e3edy3iedy0m1s3runku5szeni6lka0dziesiat8nascie7u3m2lacz2nial5ejn2ski4ucznik0a8obiecie3t0a1e1y5cha0c1l1m1ny5go0s3lana3ei1j2o2mnaty4orne4u2n0ca1u1zyl4ewka4ia1e0c0znie6u2opie4tusza6rona4sci3t2raj0u3eci0l3w0ny4oki0em3ow2u2l1pic0iel6tki0e2o2o0na5wi0a3yjomu4spa1us5zesla1e1o2zowska1i0ejAyczac4k0nal2eli5z0a5siadz2ze1ki4ecia3dza3ze1yca6ztalt6to0ra1e0go2j1mu3y0ch2m0i3zy3s1z3u0l0a2pca1em3ic1ec2l2uje4sego5westarz6iaty6lace2da2ki2lka1e3s0ach3em2ka1e1i2ow2u2t0a1wo2y3eb1ci1ka1i0ch2ego2j4z2dwie4gii3karz3ka2tyke1i5on2piej4wa1o2z0a0l2y3ica1ha3g0ia1e1i1o2ow3nus0a4scie3iecki5t2tewskich7osc0i4wa1ie2y4okaj3tr2wach3y2zka4ub0i0l3d0nosc4u1zi0e1om3ka1ie3mi5wow3zami3y3ma0ciej1k3ka3ja0c1tek2ku4or0ze5la1e1o1y2m0y2rku2szalek6uszewicz0aAsz2tka1i3z2e0go2j1ke1i2liton5za1czyzna1i8gnieniu7i0al0a1bym3em2o1y2re2sta1em2o4e0c0z2dzianobrody9y3jsca0ch3e1u4li2scie3iac2ecy4zka0l1ncow3ia1e1u8kolaj5lczal2enia1e1u4kiem6osc0i0a3ierdzie4ny7uje3y2mo2na1cel3e1ut3riam4siewiczowa9trz5loda1ego3y1zi0eniec4z0y8na1ie0j0sza6ostwo6oc0niej3o2y2da1lic1twy5y2ga0c2e1l0a1by0m3em2i1o1y3i0ch2m2j0a1e0go2j3panku5rza1e3skal0a1i1ow4wa1y4wi0a0c2c1e1l0a1em3ono3sz3y2ze0sz3na4raczewski0egoBuknal6u0ry2si0al3za1e3zyka5y0ch2m1sl0a0c1l0a1em4e0c2i0sz2wcow3i7na0d0e0szla5szedl5to2ziei1ja1e6gle3jczesciej8mniej6lezy4m0i2n1okol4poleon0a6rawde4zeciw4od5reszcie7s0tala3epnie6z0a1e0go2j2ych2m4tomiast6uralnie5y3ychmiast9uka1e1i3wet3zajutrz5riusz6wisko5ywa5eapolis6ro0na5i0a1by2c0h1zego3ym4e0ba1ezpieczenstwoDie1os3o2ch0aj2ze3o2dawno4zwiedz0ia9gdys3o2j1kiedy4tore1zy6mal0o3u2pokoj4rzyjaciolmiCraz3stety4zczescie3liwyAwolnica1y2k0a1ow8zmiernie9gdy3kogo2mu3t2m0i2z2o0c0y2g0a1e1i2s0il3wa1e0go3ina3o1y4o0ba0dwa3j1wa1y3chodzi6ecnie2ych6iad2e0cal5licze4ok3oje2k2u0racz5yczaje7chmistrzyni9ocki0ego8zach3u1y0ma2wiscie9d0bil3dac1l3e0zwal0a6nalezc6parl0a4owiada3edz0i0al0aBrzekl0a6tad4fiar0y5garnela6ien3nia3ole3rod0ach3ow2u1y1zie4mne1y6j0ca1em2iec3zyzny7ka1iem3na1em2ie2o2o0licy3o3ropnie5zyk0i6n0a1e1i2pieke4owiadal7rocz4uscil6sob0a1y3tatni0e5rianum7wiadczyl9t0o0z2worzyl7w0a0d2dzie4e1oz2szem5zenil4wal0y6pacierz5lacu2tynie2u5ce0m4mietam6n0a1em2i0a1e2na1e1ie2y2ow0ie4ski0e3twa1o4u1y2pier3o2ra1e1ku2u1y0z0a1u4s1tkiewicz7rz0a0c2cie3ec2y0l5wel2la4elna1e3troniusz0a1owi3u9wien3na1ego3ie2osc0ia5y0m5iasku4ec0dziesiat9kna1e1ie2osc3y3niadze4edzy6rs0i0ach5wej2sza1e0go2j2y0m6s0n0i3tnascie6ro1ze5ja2lnie4otr0a4sal2ze4lac1szcz4ucjusz7eban4omien5ut0a3ynie5o0chylil5iag3zal1tku4ela1i1o1y2to3ucie6d0al2czas4komorzego3y7ly2niosl0a1szy7oszac6oba1na1e0go3o1y0ch7gladal6jde2echal5sc3ki1oj0u4l0ak2e1glosem6owanie4ie3zyl4ska1i0e4u0dnie5y2miedzy4mo3oc0a3ponia1e1i5ysl0al0em8niewaz5o2ppea1i3rzednio8rwal3y1zadku6srodku5tac0i2nowil7zedl5tem2rafi2wy3zeba1uje8waznie5iadal4e0cie3dz0ial2ec5m1sci3trze5nien5odu2li2z0ow2u3stal1nie6tarzac1l5orzyl7za0r0u3egnal5nac1l2iej3o2ostal5wol0i6raca1y2wa1da1e1y2ie1l2o3edko2zej4torianie2ow8zesowa1ej8ocent2s2z2gu2si1to1u2ze3tazy4zno4usak4zecie0z2w3d0e1pokoju6tem4praszam7razenia6wal0a5stal4to2z2odu3y0chodzi0lo8jaciel0a1e6dzie4echal4mnosc6sc3klad4najmniej8patrywal7omnial7siegam5lowie5zedl3la1o7sow2y2taki2stwo6uszczy6yta0c1l1m1nia1e7rachunki5je1i2zej1k2yl4d0a1ca2e1osc0i0a5y2k1mie1ona0ch2mi3y5na1o2pier4tunku5z0em2ie2u1y3ebajlo5ce2jent0a1em6ka0ch2mi3e1i1ojesc4ma3u2szte4zultacie9obak0a3i0a1c1e1l1sz3oty4cznie5du1zaju3ina1y5g1k0u2li2wna1ie0z5zkaz0u1y3osz0y5maitych5wiac1l5owa1e1y4ne1ych4um0ial2e0m1sz8uble1i3ch2mieniec7ry2szyl5ybe2kow0a5zadca2ka1o4ecki0ego5z0a1e1y0wiscie9dem3ki1l0a1bys3em2szy6uca1il4ym0ie2ski3u5sa0d0u1y2k1li1onie2u4m0a1e0go2j2i1o1ym3siadow7ciany3skajac5nal5yzoryk0iemAedzia1ego2mu3o4n0atorow6eka4rca1e1u2wis5ie0bie3dza1i0al5ni3l0a1e1niej4y3kad2lep0ie2u3onil5oczyl4luba4nczyl5re1o3rzydla7lad1wny4onca1e3w0a0ch3em2o3uchac1j1l4dzy3ga1i2p1sznosc6zacy3ba4ychac4szac1l0em4ec6mial2echem4jac3rc0i0a7nu2oba1ie3kol3plica1e1ow0a1ie4y6pac0er4iewac1l5od0ziewal7jrzal0a3enia1e7koj0nie2y2u4lka1e1i3r0u2sob0em4trzegl0szyAtkac1l4za3rawa1y3zet4uszcza6ytal0a1em7rod0ek2ku5tac0h0a1u3d1je2l0a1i1o1y2mtad4nal2ie1slawie8ra1ca2e0go3ski0ego3m4uszka5y1zec2y3wka2ska1iej7o0i1ja0c3kroc4l0a1e0m2icy3nik0a4u2pnia1owo6sunki6rach1il3szna1e5one1ie2y3uny3yj0a3zelac2by2cow2y6u2ubiekt5kni0e4rdut4zin0a5wa1e0go2j2iat0a1em2la1o2yn0i0e6eca1i0e1ly4tle3zo4oich2m2j0a1e0j4ych2m3ycylii5n0a3zable1i3nowny6czerze3scia1e0m4liwy6wacze7edl2pnal2ela5reg2oko4sc0dziesiatBkoda4la0chcic0a4etny4ta1e1y4ngbaum0a8i1y2mer3pady3rot4tuki4uka0c1l3man0a5ybko3je5ta0cy2deusz0a6k0a1i0ch2e0go2j2m2t1ze3m1rsu4e0atru4dy2go2j1limena1ie2y6m0u2n1raz3z2lum0ow2y4o0ba1ie3masz4nem3warzystwa1ie2oAraw0ie2y3iclinium8oche4udno4woga4ybun4zeba2ch1i3y0dziesci7kroc4ma0l6u0dziez5nike4taj3z2wa0rz0a1e1y4ego3oich2m2j0a1e0j5y0ch2dzien5gellin0a1us7odni5l0e1ko2u2m0czasem6i2s0iac0e3ecy7u0cha1em3zcie3ta1e1y2uc0ia3l2ynic1l0a7dac1l2erzyl6jrzal1wszy8kazal4lonil6lice1y4marl0a4ial2lkl4rzec4yslnie7rsus0a4zad2edu5siadl4lyszal1wszy9miechem2nal8t0a0ch2mi4zy3waga1e2za5via3w0am0i2riat3szawie2y5to3s0c1owska1iej7z0e3tyniusz8cale3hodzi5iaz3zesnie5oraj6dowa4e0dle1ug4gielek6stchnal5ynus5zli5iadomo0sc0i7ra1e1y2tr0em5dac2ocznie5k1wiska1o6za0c2e1i0al0em3no3ec2sz3ow4e0c0ej2ie2zerzy4or0a1em6dz0ial2ec5ksza1e3u2le1ka1i0ch2e0go2j2m3mozny5u2m1rsze1y3zchu3e1yc1l4s0c0i2z2zienia1u7lk1li3na1em2icjusz0a1em2owi3u7o1y2osna4rski4taj3wat4kolo3rotce6lasna1e0j2ie2ym5os0cian4y4net3obec3da1y1za3jna1y2ski0ego4u4kolo3ulski0ego2mu3m7la0c1l2e1i1na1o3wczas5zny4pada1l3ol2rawdzie6ost5raz0enie6eszcie6oci0c1l1wszy7zasnal7si1kazujac7rod3tal2egi3ydu4zak0ze4edl1zie4lkie4rz3yscy2tkich2e0go3m2o7tedy2m1nczas6racil0a7y0biegl5chowanie7iagnal7daje2l0a1o2wal0o5obyl5glada0l6jechal5sc3obraz5padek5raz2ok2zekl5socki4zedl3la1i5zdluz4gledem2u4orza5ial1wszy5ela4nosi4rok0iem5uszyl8z0a0bic1l3czal2ela1i3yna5dal2en2nej2ych5jac3konczyl7l0edwie5i1u2mek2iar1st4knal3u3nim3pewne4ytal0a6raz0em4eczyny7s0cianku7tem2rzymal6ybrze6wolal0a5sze3zdy5bawiciela8iera4lizyl5oze3rodni5yt3da0je2lo2wal0o5ola3row0ie5umieniem8ziwieniem5ony8e0by0m3chce4m1rwal4s1wszad6ginal4oda1y1zic6ielonej5mi0a1e5le0go3osc2ta2zyl4y2mienia6na0c0zy3jdzie5k0i2l0azl3ezc1li5m2ow0u4obaczyc1l1my7lnierz0e1y7na1y2si0a1e1u2tac1l1nie7razu3ecznie5nice4szta5obi0c1e1l0a1o4zumial8upelnie7wal2ierz0a0t6laszcza7rocil1wszy8yczajem2u5kl0e5yc0ia1e0m2u3d0ow2zi3ja1e2l2za', '42283CC83C8348832334833333mmm32333333W888C12328C8CCW244141CmmG2WWWWWGWWmC22WW1G8G1223W2WWWW222W22228WW82WGG2WWWW1m221G1228G112111G11WG41W43W333338mm1141111G233338WWWWW1G41W28W2223mm23333W22122W8W2488W8222WGW224882248G11G4833WWWG18G1W12811WW21W2218WW884GG84124W22233W8W4m1G8GG4W12888W8WWWW1WWWWGCC1482WW2WWWWWWG482444W444mmmmm882W884W4W2128881WWW18m211GW8W84GWGW48W822288848GWGWWWW8W1W121mWG28884G223284G4G4CW3C22CCW22CCC8CWWG18412GG88CCmW2333GW11422GW12GW82118248281WG8WWWW1W3333WW22WW8C8WmCC3888CmWWmWCCW811WW8WCC338WW1221212814288881W22CCCWW1mG141824284811182W2G2G8mW184W1228114842828mm12WW248481834GW4C88WWm8C184WGG4Gm884888884WCWC2mm848C842228G4WGW2WC8WGGWmG4W8WmmW2WGWWW1WW14WWmmWW8331Wm33888CCCWWWm12W888WW2WG11212121128GGWWCC8C8CmmWWWWCCWWWWGGWW8W2W8WCCCCC2W32W33C4W4GW4GW8333333331C8m22mmm8WmW82GW2222241243W18mmm4188WmWW4G8838CC4818W4W33C8CW24G48G222222W4W31G2G4128C4W2888CWGG1W222283W18CC83CWG24WWWW1414124G1W22W12422484222444414W4m22mmmmW888G2848G42W424CC81148G4GGWW21G888884GmmG18222221488W44W3WW88G8422G4G48G82C842228238833321W41214W2WWGGW8G4WWW218223W223WW8823322W181GG12822GW8GWWG18W184Wm4228228G2WW11WWWmCC4W1G8421248838C8222823G222222W23W2WG8W888W1W8884WW8W22444122W8848WW3442882Gm2GW8822W233WWG8888848888W88W8W8WWCW888W88CWCWW8W2G122213333218W284218884W2G88W224GG88G4W22CC8WW3248W23m2mmW11C22222223G88mm81128W118844W2822488WW8m84WWWW8WW8213332888m332W8WWW228G2WG8WW4m4844W282G8C8WW21882284G8G22888WG228844433CCCW2WWW88mGm8W211C283W8231W142GWW288118882W111WWWmWW2882288C2CWWWCW212GW1224mW8m24G288mGWWWW1W44W1WWCWW88888888W2WWW88WWW222W22881GGGWWG28888C48mW2Wm8mWCCW2m42W218W82W422324WWWm8C811G18W44WW8WmWWWWW22311GW44WWGW222228888WWm4WGWWWGG222GWG21WGWW281WW2G218W222214mmmmmmm4C22G248888242CCCWW88882488GWm888mWW1CCCWWWGW1W4G1C1WW1CCCC41WCCC8WWW2Gm4WWmmW28C24124WWWWWWmWm8C8W8CCWW8G11112223WWGW2W84G844WW211Wm8W11W1mG88GW8C4WWW2WWWCC2WWWCGW2GCC8G18mmG4844444W2G3GC414mmmm441GG2242188888mWW38G13GG888WWWGW38WW222222222212183338WG4W4182W18GWW222288433322G22484882222233WW812882G12W4883G1GC884WmCCWG38W8W88GW8883GG18222WWW22221G44112242441WW41821G224WGWWW1WGWG422W222WW2123W321333332GWC2WWG22141Wm2W214WWWmmWWCCCCW2W12W82WWGW222822242WW824WWWW8W2mW2G2148Wm8CW8W182222288884C842WC48WG82242WWW12G42G88W8WG14W81221W888W2488G2m2m11348Gm2W2W21W8W1828W22W1G81141WWWWWWW1144GG8GWW144W2G422828888W2244mmmWG11WWW888888822WWW2222WWW112221888WGGW', 'rkAMAnRnPBn99aXP99EsoRBooLRRRKcjkkkqLjhpjTETshRhRUkTjjsrSjTRRpRhjhjTsE99EajRhTP9BsjppURphCZ99hRTphssRhkphsTsjUU9srUjhRTkhhjrhRsRTTRfDTqTrhjkssjrUjrIRRjjrrjRRssUaaZRsshhjRTshSjTskrssUThRUsjjjrkjSrRUrjDsssMARIpgIoshRhrRIcf9khrkjTpTUUprrsrpn9DjkkMqIBsKscIpjrUI9TphRRTRUsTTILhbRhRRpRRTkjSrUrRTRUUUaRshRRnssJsqoRskTcsURRooicUMRRUrrjMsscrsarssrjkrajnDi9poIjqjsssjpRRRRRjsIQoakrIsrjssUsIILnT9Jsksp9999gSRacqhkrTRRRDUacUUcksnoJRrr9MMhsUhTRpfkkrRJpRQrjhRREUInLrUspRRUrpUjRRRRURpTSjaasRpRTRpRIRhsrrhkRRRqbhhjhRTsfsRspUsspQRhhfU9DURTTkjrTrjRpPrPrRPDjRThkRksrpUkUZRRUpkRsqITjRhRpBJRRPhRjTPjksRrkssssTpphpUsfUUTijhrkfDssspssssssospsogjrURRf9BhpRTpUrpTjsprUjIsfRUfZajgRRRPhSchkrhpTRTsshZUsksrP9RRXBkrhRpsUkZRThUorpRTksURsspUsR9IMksUbZrRJnsPThUrURhRURTjbrRRpJMjLjjhjSpZrRqkspkrToksspshskrjTjjpUjkrRUMqhiSoMSRphkkpfUjqorURhUhqssrPjkRssRRUUrirkjjjkrjjkUkhhRpRRSaaaQjjssRRIMpRTprqRSkQIsjjhrJkQIMkIMjjqricRJRRrksccMsIjTThTfrjTspUjjkchUSsspMkpsoLjojjITRappRprnoRSaZrjRRksUcnsPssTrsEjhhTjRhR9BkUTrpUsjjpn9hrhpRTRfDkhpjhhUDjMpiIjEshUhUDpTTjpRjhrjhURjRTjRssskshRpRrhPnT99DjLrhRpijTrrarIIrhjRsrRhhhUpUjjUSrhUTZMshRRUpUJrosjRUkrhsjsssRsThpUppsSShBUbhjkTRhhUUpRjsrrjRjTkkTjRUkRTjsacjTrRsspTjjhrjhTUUjj')

def b64_expand(string, bits):
    assert 6 % bits == 0
    bi = "".join(bin(b64.find(b))[2:].zfill(6) for b in string)
    return [int(bi[i:i+bits], 2) for i in range(0, len(bi), bits)]
def string_run_decompress(data):
    curr = ""
    for c in data:
        if c.islower():
            curr += c
        else:
            if curr: yield curr
            for i in range(b64.find(c)):
                curr = curr[:-1]
    yield curr

dictionary, claim_raw, exist_raw = raw
dictionary = list(string_run_decompress(dictionary))
claim = b64_expand(claim_raw, 2)
exist = b64_expand(exist_raw, 1)

claims = [[set() for _ in range(4)] for _ in range(3)]
for i, (c, e) in enumerate(zip(claim, exist)):
    if e & 1:
        #print(i%3, c&3, dictionary[i//3])
        claims[i%3][c & 3].add(dictionary[i//3])
    c >>= 2
    e >>= 1

special = (
    (0, 2, '"'), (0, 2, ';'), (1, 2, "'"), (1, 2, '-'),
    (1, 2, '.'), (0, 1, '!'), (1, 1, '?'), (2, 1, ','),
    (0, 0, ','), (0, 0, '?'), (1, 0, '!'), (1, 0, '"'),
    (1, 0, ';'), (2, 0, "'"), (2, 0, '-'), (2, 0, '.')
)
for i, k, w in special:
    claims[i][k].add(w)


# claims = [[set(c.split()) for c in C] for C in raw_claims]

names = ["Mickiewicz", "Prus", "Sienkiewicz"]
weights = [1, 2, 6, 65536]


def get_words(text, pun=True):
    words = [w.strip(".,?!:;'\"()[]-") for w in text.lower().split()]
    words = [w for w in words if w]
    if pun: words.extend([c for c in text if c in ".,?!:;'\"()[]-"])
    return words

def rhyme_coefficient(text):
    words = get_words(text, False)
    et = {}
    d = 0
    gap = 7
    for i in range(len(words)):
        ed = words[i][-3:]
        if ed in et and et[ed] >= i - gap and words[i] != words[et[ed]]:
            d += 1
        et[ed] = i
    d = d / len(words) * gap
    return d

def isvowel(c):
    return c.lower() in "aeiouy"
def count_vowels(text):
    return sum(isvowel(c) for c in text)
def count_diftongs(text):
    return sum((a+b) in ("ie", "ia", "au") for a, b in zip(text, text[1:]))
def upper_vowel_distance(text):
    U = [i for i, c in enumerate(text) if c.isupper()]
    V = [count_vowels(text[U[i]:U[i+1]]) - count_diftongs(text[U[i]:U[i+1]]) for i in range(len(U)-1)]
    return V
def trzynastozgloskowiec_rating(text):
    V = upper_vowel_distance(text)
    S = [0]
    for v in V: S.append(S[-1] + v)
    result = 0
    a = 0
    for b in range(1, len(V)+1):
        while S[b-a] > 14:
            a += 1
        if 12 <= S[b-a] <= 14:
            result += 1
    return 100 * result / count_vowels(text)

def solve(text):
    words = get_words(text)
    decision = []
    clcnts = []
    for i in range(3):
        clcnt = [0 for _ in range(4)]
        for l, c in enumerate(claims[i]):
            for w in words:
                if w in c:
                    clcnt[l] += 1
        clcnts.append(clcnt)
        decision.append(sum(g*v for g, v in zip(weights, clcnt)))
    upper_c = sum(c.isupper() for c in text) / len(words)
    if upper_c >= 0.04:
        decision[0] += 8
        decision[1] += 4
    if rhyme_coefficient(text) >= 0.5:
        decision[0] += 16
    elif len(words) >= 50:
        decision[0] -= 32
    decision[2] += 6
    if len(text) <= 2000:
        decision[1] += min(64, max(0, text.count("...")-2)*8)/2
        decision[1] += min(64, max(0, text.count(" - ")-2)*8)/16
        decision[0] += 2*trzynastozgloskowiec_rating(text)
    Y = decision.index(max(decision))
    return names[Y]

for text in sys.stdin.read().strip().split('\n')[1:]:
    print(solve(text))
