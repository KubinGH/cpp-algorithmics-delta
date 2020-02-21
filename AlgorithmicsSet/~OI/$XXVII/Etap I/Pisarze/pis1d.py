import sys

raw_claims = [
    ['? aby ach albo alez anizeli azeby bardzo barona bogow boze by byl byla byli byly cale calym chcac chcial chrystus ciebie co coraz coz czasie czesc dobrze doktor domu dosc dotad drodze droga drogi drugi drzwi dusza dusze dwadziescia dwu dzieci dzieje dziesiec dzis gdy glos glowe i ich imie innych iz jakby jakoz je jeden jedna jednej jesli jezeli kiedy kobieta kobiety kolo ksiaze lat lecz lub lud ma majatek mam miasta miedzy moglo nad nareszcie nas nauka ni niewolnikow nigdy niz no obok oczy odezwal okolo on otoz ow pan pana panem pani panna panne pannie panny panowie panu pare paryza patrzac piec piersi po podniosl pokoju pol prawie prawo procz prosze przeciw przed przy ramiona razy reke robi robic rok roku rzekl rzymie sa sam serca serce skad sklepie sklepu slow slowa slyszal smierc soba spojrzal stalo stary sto swiata swoich swoim szepnal taki takze ten teraz tobie tomasz trzy twarz twoj twoje ty tymczasem umial ust wam wcale wciaz widzial widzialem widziec wie wiedzial wlasnie woli wraz wreszcie wszystkich wszystkie wszystko wyszedl wzial za zaczal zali zbyt znow znowu zrobic zrobil zwrocil', '! , bez blisko bo bog bylem cala calej chociaz cicho czas czasem czesto dal dawniej dosyc druga drugiej dwa dwie gdzie glowa glowy gory idzie jak juz kazdy kaze koncu konia kto ktoz ku mial moj mowiac my na nalezy nam naprzod nasz nasze niebo niech nieco niegdys nieraz nikt nim nogi oczu oczyma pierwszy pod potem prawda przerwal rak raz razem rece reku rownie sami siedzial slowo swa swej swiecie swoj swych tak tam te tez trzeba tu tyle u usta w widzac widzi wielka wielkie wolna z zaraz zawsze zeby', '" ; az biala biale bracia bracie bron choc czyli dawno dlugo drzewa dwoch dworu dworze glupi gosci goscie hrabia hrabiego jako jeneral koniec kraju krzyknal ksiadz ksiedza ksztalt las lasu lata ledwie lubil major mlodziez niby niedzwiedz oba okiem ostatni panow pewnie pole pomiedzy prawa przeciez rad rejent reka robak rykow rzecz sedzia sedziego sedziemu siedzi slychac srodku stad stal stolu strony swe swym szlachcic szlachta szlachty tuz tylu was we wiatr widac wiele wielki wiwat wkolo wnet wola wolal wozny wpol wszak wszyscy wtem wy wzrok zamek zamku zdrowie ziemi znak zwierza', 'asesor bernardyn biezy dabrowski dobrzynscy gerwazy horeszkow jacek klucznik litwie maciej moskali podkomorzy protazy soplica soplicow srod strzelcy tadeusz tadeusza telimena wojski wojskiego wtenczas zosi zosia'],
    ['! " ; bardziej beda bedzie bez bo bowiem bracie bron byc bylem bylo bym caly choc chocby chociaz chrystusa chrzescijan chwila chwilami chwile chwili ci cicho cie czasu czul czym dalej dawno dla dlaczego dlatego dom dosyc druga drzewa duszy dwa gdyby gdyz gdzie glosem glowa glowie glupi go gory gosci hrabia hrabiego idzie im inaczej inne inni istotnie ja jaka jakas jakie jakies jakkolwiek jednak jednakze jego jej jeneral jeszcze juz kazal kazdy koncu konia kraju krzyknal ksiadz ksiedza kto ktora ktore ktorego ktorej ktory ktorych ktorym ktorzy las lasu lata ledwie lepiej lubil ludzi ludzie major mial miasto miescie milosc milosci mimo mlodziez mna mniej mogl mogla moim moj moja moje mowiac mowic mowil mu my mysl nagle nam naprzod nastepnie nasz nasze nia niby nich nie niech niego niej nieraz nimi noc nocy nogi nowe oba od odpowiedzial odrzekl okiem ona oni ostatni oto panow patrzec patrzyl pawel pewnie poczal poczela poczeli poczely pomiedzy potem powodu prawa prawda przeciez przerwal przez raz razie rejent rowniez rzecz rzeczy rzym rzymu sama sedzia sedziego sedziemu sie siedzi siedzial slowo slychac smierci sobie srodku stad stolu swiat swoj swoje szczescie szlachcic szlachta szlachty ta takich takim tam tego tlumy toba tu twarza twarzy twoja tych tyle tylu tym u we widocznie widok widzi wiecej wiele wielka wielki wielkie wiesz wiezienia wiwat wobec wola wowczas wozny wprawdzie wprost wsrod wszystkim wy zamek zamku zaraz zarazem zas zawsze ze zupelnie zycia zycie zyciu', '? a ale ani bede chce ciagle co cos czego czy dni dnia do dobrze drugi drzwi dzien dzis gdybym jaki jeden jedno jest jestes jutro kilku ktos lat maja masz mi miala miec mlody mnie moge moze mozna musi musze mysli nas nic o on panie piekna pol prawo reke sa siebie skad spojrzal stary swego swoich swoim taka takie tej temu ten to trzy tylko wciaz wie wiec wiem wlasnie wszystko wyszedl wzial za zamiast zawolal zdawalo zle', '- . ach albo alez anizeli azeby bardzo barona boze chyba coz czlowiek czlowieka dodal doktor dopiero dwadziescia dwu dziesiec ile interes jakis jestem jezeli kiedy kilka kobieta kobiety ksiaze list ma majatek mam mowi mowie mowila mruknal myslal mysle naprawde nareszcie nawet no odezwal odparl odpowiedziala ojca ojciec okolo otoz pan pana panem pani pania panna panne pannie panny panowie panu pare paryza patrzac piec pieniadze pieniedzy pokoju pomyslal poniewaz pozniej prawie prosze przecie przynajmniej razy robi robic rok roku rozumiem rzekla sklep sklepie sklepu sposob spytal sto swoja szepnal taki tomasz troche tysiecy ulicy wcale wszedl wtedy wtracil zaczal zapytal zawolala zdaje znam znowu zreszta zrobic zrobil', 'adwokat baron baronowa baronowej fotelu geist hrabina ignacy izabela izabele izabeli lecki maruszewicz mraczewski naturalnie ochocki prezesowa rubli rzecki stach starski stawska stawskiej szlangbaum szuman wasowska wokulski wokulskiego wokulskiemu wokulskim'],
    [', - . a ale ani az bede biala biale blisko bog bracia cala calej chce chyba ciagle cos czas czasem czego czesto czlowiek czlowieka czy czyli dal dawniej dlugo dni dnia do dodal dopiero drugiej dwie dwoch dworu dworze dzien gdybym glowy goscie ile interes jak jaki jakis jako jedno jest jestem jestes jutro kaze kilka kilku koniec ksztalt ktos ktoz ku list maja masz mi miala miec mlody mnie moge mowi mowie mowila moze mozna mruknal musi musze myslal mysle mysli na nalezy naprawde nawet nic niebo nieco niedzwiedz niegdys nikt nim o oczu oczyma odparl odpowiedziala ojca ojciec pania panie piekna pieniadze pieniedzy pierwszy pod pole pomyslal poniewaz pozniej przecie przynajmniej rad rak razem rece reka reku robak rownie rozumiem rykow rzekla sami siebie sklep sposob spytal stal strony swa swe swego swej swiecie swoja swych swym tak taka takie te tej temu tez to troche trzeba tuz tylko tysiecy ulicy usta w was wiatr widac widzac wiec wiem wkolo wnet wolal wolna wpol wszak wszedl wszyscy wtedy wtem wtracil wzrok z zamiast zapytal zawolal zawolala zdaje zdawalo zdrowie zeby ziemi zle znak znam zreszta zwierza', 'bedzie byl byla byli bylo byly bym cale caly calym chcial chocby chwile coraz czasie czasu czul dalej dla dlaczego dom domu dosc droga drogi dzieci dzieje gdy gdyby glos glowe go i ich im innych ja jaka jakie jakies je jedna jednej jeszcze kazal ktora ktorej ktory ktorym lepiej miedzy mna mniej moim moja moje mowil mu nad nagle nich nie niej nigdy nowe obok oczy od ona oni patrzyl po podniosl przed przez przy rzeczy rzekl sam sama serca serce sie soba sobie stalo swiat swiata swoje szczescie ta takich takim tego teraz tobie tych tym tymczasem widzial widzialem wiecej wiedzial wiesz wszystkie wszystkim zbyt ze zyciu', 'aby bardziej beda bogow bowiem by byc chcac chrystus chrystusa chrzescijan chwila chwilami chwili ci cie ciebie czesc czym dlatego dotad drodze dusza dusze duszy gdyz glosem glowie imie inaczej inne inni istotnie iz jakas jakby jakkolwiek jakoz jednak jednakze jego jej jesli kolo ktore ktorego ktorych ktorzy lecz lub lud ludzi ludzie miasta miasto miescie milosc milosci mimo mogl mogla moglo mowic mysl nastepnie nauka ni nia niego niewolnikow nimi niz noc nocy odpowiedzial odrzekl oto ow patrzec pawel piersi poczal poczela poczeli poczely powodu procz przeciw ramiona razie rowniez rzym rzymie rzymu slow slowa slyszal smierc smierci takze tlumy toba twarz twarza twarzy twoj twoja twoje ty umial ust wam widocznie widok widziec wiezienia wobec woli wowczas wprawdzie wprost wraz wreszcie wsrod wszystkich zali zarazem zas znow zupelnie zwrocil zycia zycie', 'akte albowiem ancjum apostol apostola atrium aulus aulusow bogowie cezar cezara chilo chilon chilona chrzescijanie eunice ligia ligie ligii ligio nero nerona niemal niewolnicy ostrianum petroniusz petroniusza piotr pomponia pomponii poppea tygellinus ursus winicjusz winicjusza winicjuszowi']
]
claims = [[set(c.split()) for c in C] for C in raw_claims]

names = ["Mickiewicz", "Prus", "Sienkiewicz"]
weights = [1, 2, 6, 65536]


def get_words(text):
    words = [w.strip(".,?!:;'\"()[]-") for w in text.lower().split()]
    words = [w for w in words if w]
    words.extend([c for c in text if c in ".,?!:;'\"()[]-"])
    return words

def rhyme_coefficient(text):
    words = [w.strip(".,?!;'\"()[]-") for w in text.lower().split()]
    words = [w for w in words if w]
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
    decision[2] += 4
    Y = decision.index(max(decision))
    return names[Y]

for text in sys.stdin.read().strip().split('\n')[1:]:
    print(solve(text))
