const questions = {
    1: {
        quest: 'Melyik a Föld legnagyobb óceánja?',
        awser1: 'Csendes-óceán',
        awser2: 'Atlanti-óceán',
        correct: '1'
    },
    2: {
        quest: 'Hány perc van egy órában?',
        awser1: '30',
        awser2: '60',
        correct: '2'
    },
    3: {
        quest: 'Melyik bolygó a Naprendszer legnagyobb bolygója?',
        awser1: 'Jupiter',
        awser2: 'Mars',
        correct: '1'
    },
    4: {
        quest: 'Mi az alma fő színe?',
        awser1: 'Zöld',
        awser2: 'Piros',
        correct: '2'
    },
    5: {
        quest: 'Mi a fővárosa Magyarországnak?',
        awser1: 'Budapest',
        awser2: 'Debrecen',
        correct: '1'
    },
    6: {
        quest: 'Hány nap van egy évben (szökőéven kívül)?',
        awser1: '365',
        awser2: '366',
        correct: '1'
    },
    7: {
        quest: 'Melyik az emberi test legnagyobb szerve?',
        awser1: 'Tüdő',
        awser2: 'Bőr',
        correct: '2'
    },
    8: {
        quest: 'Mi a víz kémiai képlete?',
        awser1: 'H2O',
        awser2: 'CO2',
        correct: '1'
    },
    9: {
        quest: 'Melyik évben történt a holdraszállás?',
        awser1: '1969',
        awser2: '1971',
        correct: '1'
    },
    10: {
        quest: 'Milyen állat a delfin?',
        awser1: 'Hal',
        awser2: 'Mammália',
        correct: '2'
    },
    11: {
        quest: 'Melyik a legmagasabb hegy a világon?',
        awser1: 'K2',
        awser2: 'Everest',
        correct: '2'
    },
    12: {
        quest: 'Mi a magyar himnusz címe?',
        awser1: 'Tavaszi Szél Vizet Áraszt',
        awser2: 'Szózat',
        correct: '2'
    },
    13: {
        quest: 'Hány kontinens van a Földön?',
        awser1: '5',
        awser2: '7',
        correct: '2'
    },
    14: {
        quest: 'Mi a Föld középpontja?',
        awser1: 'Mag',
        awser2: 'Kéreg',
        correct: '1'
    },
    15: {
        quest: 'Melyik a legnagyobb szárazföldi állat?',
        awser1: 'Elefánt',
        awser2: 'Zebra',
        correct: '1'
    },
    16: {
        quest: 'Melyik fém olvad 660 °C-on?',
        awser1: 'Vas',
        awser2: 'Ón',
        correct: '2'
    },
    17: {
        quest: 'Melyik sportágban használnak kosarat?',
        awser1: 'Foci',
        awser2: 'Kosárlabda',
        correct: '2'
    },
    18: {
        quest: 'Mi a napenergia forrása?',
        awser1: 'Föld',
        awser2: 'Nap',
        correct: '2'
    },
    19: {
        quest: 'Mi a fővárosa Szlovákiának?',
        awser1: 'Pozsony',
        awser2: 'Kassa',
        correct: '1'
    },
    20: {
        quest: 'Hány csont van egy felnőtt emberi testben?',
        awser1: '206',
        awser2: '195',
        correct: '1'
    },
    21: {
        quest: 'Melyik a legnagyobb mértékegység a terület mérésére?',
        awser1: 'Acre',
        awser2: 'Hektár',
        correct: '2'
    },
    22: {
        quest: 'Honnan származik a pizza?',
        awser1: 'Olaszország',
        awser2: 'Spanyolország',
        correct: '1'
    },
    23: {
        quest: 'Mi a leggyakoribb gáz a légkörben?',
        awser1: 'Oxigén',
        awser2: 'Nitrogén',
        correct: '2'
    },
    24: {
        quest: 'Ki írta a "Hamlet" című drámát?',
        awser1: 'Shakespeare',
        awser2: 'Goethe',
        correct: '1'
    },
    25: {
        quest: 'Melyik a leggyorsabb állat a földön?',
        awser1: 'Gepárd',
        awser2: 'Puma',
        correct: '1'
    },
    26: {
        quest: 'Melyik tenger határolja Magyarországot?',
        awser1: 'Fekete-tenger',
        awser2: 'Nincs tenger',
        correct: '2'
    },
    27: {
        quest: 'Mi az emberi test fő vérkeringési szerve?',
        awser1: 'Tüdő',
        awser2: 'Szív',
        correct: '2'
    },
    28: {
        quest: 'Mi a legnépszerűbb társasjáték a világon?',
        awser1: 'Monopoly',
        awser2: 'Scrabble',
        correct: '1'
    },
    29: {
        quest: 'Ki a híres festő, aki "A Sikló" című festményt készítette?',
        awser1: 'Da Vinci',
        awser2: 'Michelangelo',
        correct: '1'
    },
    30: {
        quest: 'Milyen formája van a Földnek?',
        awser1: 'Kocka',
        awser2: 'Gömb',
        correct: '2'
    },
    31: {
        quest: 'Melyik állat a legnagyobb repülő állat?',
        awser1: 'Albatrosz',
        awser2: 'Holló',
        correct: '1'
    },
    32: {
        quest: 'Mi a kémiai képlete a sót?',
        awser1: 'NaCl',
        awser2: 'KCl',
        correct: '1'
    },
    33: {
        quest: 'Hány szívvel rendelkezik egy polip?',
        awser1: '2',
        awser2: '3',
        correct: '2'
    },
    34: {
        quest: 'Melyik a legnagyobb kiterjedésű ország a világon?',
        awser1: 'Oroszország',
        awser2: 'Kanada',
        correct: '1'
    },
    35: {
        quest: 'Melyik az első könyv a Bibliában?',
        awser1: 'Zsoltárok',
        awser2: 'Teremtés könyve',
        correct: '2'
    },
    36: {
        quest: 'Mi a fővárosa Franciaországnak?',
        awser1: 'Párizs',
        awser2: 'Marseille',
        correct: '1'
    },
    37: {
        quest: 'Mi az alapanyaga a papírnak?',
        awser1: 'Fa',
        awser2: 'Fém',
        correct: '1'
    },
    38: {
        quest: 'Ki volt az első ember a Holdon?',
        awser1: 'Buzz Aldrin',
        awser2: 'Neil Armstrong',
        correct: '2'
    },
    39: {
        quest: 'Mi a legnépszerűbb sport a világon?',
        awser1: 'Foci',
        awser2: 'Kosárlabda',
        correct: '1'
    },
    40: {
        quest: 'Melyik szín a magyar zászló középső sávjában található?',
        awser1: 'Piros',
        awser2: 'Fehér',
        correct: '2'
    },
    41: {
        quest: 'Hány gyűrűje van a Szaturnusz bolygónak?',
        awser1: '1',
        awser2: '9',
        correct: '2'
    },
    42: {
        quest: 'Ki volt a magyar kormányzó 1920 és 1944 között?',
        awser1: 'Horthy Miklós',
        awser2: 'Károlyi Mihály',
        correct: '1'
    },
    43: {
        quest: 'Melyik állat a legnagyobb a világon?',
        awser1: 'Kék bálna',
        awser2: 'Elefánt',
        correct: '1'
    },
    44: {
        quest: 'Ki volt az első nő, aki Nobel-díjat nyert?',
        awser1: 'Marie Curie',
        awser2: 'Lise Meitner',
        correct: '1'
    },
    45: {
        quest: 'Melyik bolygón azonos a Vörös bolygóval?',
        awser1: 'Mars',
        awser2: 'Jupiter',
        correct: '1'
    },
    46: {
        quest: 'Mi a víz forráspontja?',
        awser1: '90 °C',
        awser2: '100 °C',
        correct: '2'
    },
    47: {
        quest: 'Mi a legnagyobb óceán?',
        awser1: 'Atlanti-óceán',
        awser2: 'Csendes-óceán',
        correct: '2'
    },
    48: {
        quest: 'Melyik nyelvet beszélik leginkább a világon?',
        awser1: 'Angol',
        awser2: 'Mandarin',
        correct: '2'
    },
    49: {
        quest: 'Ki volt a híres görög filozófus, aki a Szókratész tanítványa volt?',
        awser1: 'Platon',
        awser2: 'Arisztotelész',
        correct: '1'
    }
};