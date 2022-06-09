# TKOM Project - Skner - dokumentacja wstępna
Jakub Budrewicz

## Spis treści
1. [ Wstęp ](#wstep)
2. [ Opis funkcjonalności ](#opis)
3. [ Przykłady ](#przyklady)
4. [ Specyfikacja i składnia ](#specyfikacja)
5. [ Szczegóły implementacyjne ](#implementacja)
6. [ Uruchamianie ](#uruchamianie)
7. [ Testowanie ](#testowanie)
8. [ Dalsze rozszerzenia ](#rozszerzenia)

## Wstęp <a name="wstep"></a>
Skner jest językiem funkcyjnym stworzonym z przeznaczeniem do programowania muzyki, 
którego podstawą jest referencyjne traktowanie wszystkich zmiennych.
Język inspirowany jest funkcjonalnościami języka programowania wizualnego Pure Data oraz składnią Lua.


## Opis funkcjonalności <a name="opis"></a>
Najważniejszym wymaganiem języka jest możliwość korzystania z "funkcyjnych" zmiennych; oznacza to w rozumieniu tego projektu, 
że domyślnie, wartości zmiennych nie są kopiowane i zawsze, jeśli nie wskażemy inaczej, po przekazaniu
zmiennej do funkcji/innej zmiennej/tablicy, przechowującej ten sam typ danych,
możemy modyfikować wyjście lub wartość tych funkcji/innej zmiennej/tablicy za pomocą tej pierwszej zmiennej. 
Takie podejście jest uproszczeniem przepływu danych z języka programowania wizualnego Pure Data.

W Skner nie ma standardowych zmiennych, zamiast nich używane są lambdy (w tej dokumentacji w 
rozumieniu zmiennej, zawsze chodzi o lambdę).

Takie podejście stwarza szereg problemów:
- Każda zmienna jest przechowywana w pamięci jako drzewo operacji
  - jest to znacznie mniej efektywne niż przechowywanie samej wartości, lub referencji
- Po usunięciu zmiennej należy zaktualizować zmienne korzystające z niej
  - po usunięciu lambdy, wszystkie jej referencje są podmienione na jej ostatnią wartość
  - utrudnia to implementację, ponieważ należy przechowywać zależności pomiędzy lambdami w obydwie strony
- Po użyciu funkcji w wyrażeniu lambdy, lambda przechowuje referencję do tej funkcji
oraz jej argumentów
- Stałe wartości (literały oraz użycia operatora $), będące częścią lambdy muszą być przechowywane i usuwane 
razem z daną lambdą (są jej bezpośrednio podległe)

Funkcje w Skner nie mogą operować na globalnych identyfikatorach lambdach stworzonych przez użytkownika. Muszą one 
zostać przekazane za pomocą argumentów pozycyjnych.

Funkcje mogą za to operować na wszystkich wbudowanych słowach kluczowych oraz jakichkolwiek innych funkcjach 
stworzonych przez użytkownika, lub wbudowanych. 

Funkcje nie mogą być przeładowywane, identyfikatory są unikalne.

### Wymagania funkcjonalne:

- Interpretowanie plików

- Interpretowanie bezpośrednio z konsoli

- Zgłaszanie błędów znalezionych podczas interpretacji

- Obsługa typów liczbowych oraz logicznych (number i boolean)

- Definiowalne przez użytkownika lambdy (odpowiedniki zmiennych)

- Definiowalne przez użytkownika funkcje

- Funkcyjny charakter zmiennych osiągnięty ma być za pomocą wymuszenia lambd

- Możliwość używania lambd jako zwykłych, niereferencyjnych zmiennych (operator $)

- Statyczne typowanie

- Mutowalność zmiennych


## Przykłady <a name="przyklady"></a>

Przykładowy program:
```
>>> number function add_numbers(number a, number b)
...   return a+b;
... end
>>> number num1; # 0 by default
>>> number num2; = 30
>>> number num3; = add_numbers(num1, num2)
>>> println(num3);
30
>>> num1 = 15;
>>> println(num3);
45
>>> ~num1; # wraz z usunięciem num1, jej referencje są podmieniane  
>>>       # na kopię jej ostatniej wartości
>>> println(num1);
Error: num1 identifier does not exist
>>> println(num3);
45
>>> println(num2);
30
>>> number num1 = 1;
>>> number num2 = 2;
Error: num2 identifier already exists
>>> num2 = 2;
>>> println(num3);
17
```

Przykładowy program 2 (lambdy i pętle):
```
>>> number num1 = 1;
>>> number num2 = 2;
>>> number num3 = num1 + num2;  # lambda
>>> println(num3);
3
>>> # num3 jest w poniższej konstrukcji "rozpakowywana" do lambdy
>>> num3 = num3 + num1;
>>> # powyższe wyrażenie jest zinterpretowane tak samo, 
>>> # jak wyrażenie num3 = (num1 + num2) + num1
>>> # (jest przechowywane w pamięci w dokładnie taki sam sposób)
>>> println(num3);
4
>>> number i = 3;
>>> while(i > 0)
...   num3 = num3 + num2;
...   println(num3);
...   i = i - 1;
>>> end
6
8
10
>>> # pod koniec pętli, lambda num3 będzie przechowywana w pamięci analogicznie, 
>>> # co następująca:
>>> # num3 = ((((num1 + num2) + num1) + num2) + num2) + num2 
>>> num1 = 2;
>>> println(num3)
12
>>> num3 = 0;
```


Przykładowy program 3:
```
>>> number num1 = 1 + 1; 
>>> # num1 jest zawsze przechowywana jako (num1 = 1 + 1);
>>> num1 = num1 # <=> num1 = $num1;
>>> num1 = $(1 + 1) # takie wyrażenie jest przechowywane w pamięci jako (num1 = 2);
```

Przykładowy program 4 - pętle:
```
>>> number num3 = 3;
>>> number i = 1;
>>> while(i <= 3);
...   num3 = num3 + i;
...   println(num3);
...   i = i + 1;
>>> end
4
7
12
>>> # opis poszczególnych kroków:
>>> # i=1: num3 = (3) + i (= 4)
>>> # i=2: num3 = ((3) + i) + i (= 7)
>>> # i=3: num3 = (((3) + i) + i) + i (= 12)
>>> println(num3);
12 
>>> ~i;
>>> # po operacji ~i, wszystkie referencje do "i" zostają zastąpione
>>> # jej ostatnią wartością, a więc 
>>> num3 = (((3) + 3) + 3) + 3 (=12);
```

Przykładowy program 5 - pętla + kopiowanie:
```
>>> number num3 = 3;
>>> number i = 1;
>>> while(i<=3)
...   num3 = num3 + $i;
...   println(num3);
...   i = i + 1;
>>> end
>>> # opis poszczególnych kroków:
>>> # i=1: num3 = (3) + 1 (= 4)
>>> # i=2: num3 = ((3) + 1) + 2 (= 6)
>>> # i=3: num3 = (((3) + 1) + 2) + 3 (= 9)
>>> println(num3);
9  
```

Program zgodny ze składnią języka, ale prezentujący funkcjonalności, które nie zostaną dodane do języka w ramach 
projektu TKOM ze względu na zbyt duży zakres (wbudowane funkcje muzyczne/do obsługi audio, tablice oraz typ `sequence`).

```
>>> println(list_interfaces()); # get table of computers audio interfaces (table of strings)
audio_interface_a, audio_interface_b
>>> println(string(select_interface("audio_interface_a")));
true
>>> start(); # start audio (and clock)
>>> number function osc_dummy(number multiplier) 
...     return sin(get_tic() / multiplier);
... end
>>>
>>> number a = 15;
>>> dac__add_play_function(osc_dummy(a)); # audio starts playing
>>> a = 60; # played frequency changes
>>> println(string(dac__list_play_functions()));
dac_osc_dummy
>>> dac__remove_play_function(0);
>>> ~a # delete "a" variable and everything that has a reference to it
>>> # using native oscillator function (sinewave by default)
>>> number osc_1_frequency = 500;
>>> dac__add_play_function(oscillator(osc_1_frequency)); # play 500 Hz sinewave
>>> osc_1_frequency = 440; # change played frequency
>>> dac__remove_play_function(0); # remove dac_oscillator_1
>>>
>>> # using sequences
>>> println(string(get_bpm()));
123
>>> set_bpm(120); # set global bpm value
>>> table seq_frequencies = [osc_1_frequency,0,412,323,880];
>>> sequence seq_1 = sequence(seq_frequencies, [2,1,1,1,1], 1) ;
>>> # seq_1 value represents frequency (number) and changes in time
>>> dac__add_play_function(oscillator(seq_1)); # sequence seq_1 is now playing
>>> a=2000 ;# change first note frequency in seq_1 
>>> stop() ;# stop audio
```
## Specyfikacja i składnia <a name="specyfikacja"></a>

Lista zdefiniowanych słów kluczowych:
`function`, `if`, `elif`, `else`, `while`, `return`, `number`, `boolean`, `break`, `continue`, `or`, `and`, `true`, `false`, `end`, `exit`

Enum tokenów:
```c++
enum TokenType {
/*-------------------- literals -------------------*/
    T_NUMBER_LITERAL = 256,
    T_BOOLEAN_LITERAL = 257,
    T_STRING_LITERAL = 258,

    /*-------------------- keywords -------------------*/
    /* functions  */
    T_FUNCTION = 259,
    T_CONTINUE = 260,
    T_BREAK = 261,
    T_RETURN = 262,

    /* statements */
    T_WHILE = 263,
    T_IF = 264,
    T_ELIF = 265,
    T_ELSE = 266,
    T_END = 267,

    /* type specifiers */
    T_NUMBER = 268,
    T_STRING = 269,
    T_BOOLEAN = 270,

    /* literals */
    T_TRUE = 271,
    T_FALSE = 272,

    /*------------------ identifiers ------------------*/
    T_IDENTIFIER = 273,

    /*------------------- operators -------------------*/
    T_GREATER_EQUAL = 274, // >=
    T_LESSER_EQUAL = 275, // <=
    T_GREATER = 276, // >
    T_LESSER = 277, // <
    T_NOT_EQUAL = 278, // !=
    T_EQUAL = 279, // ==
    T_NEGATE = 280, // !
    T_ASSIGNMENT = 281, // =

    /* single character */
    T_OR = '|',
    T_AND = '&',

    T_EVALUATE = '$',
    T_PLUS = '+',
    T_MINUS = '-',
    T_DIVIDE = '/',
    T_MULTIPLY = '*',
    T_MODULO = '%',
    T_DELETE = '~',

    /*------------------ punctuators ------------------*/
    T_COMMA = ',',
    T_OPEN_BRACKET = '(',
    T_CLOSE_BRACKET = ')',

    /*--------------------- other ---------------------*/
    T_SEMICOLON = '\n',
    T_ETX = 282,
    T_UNDEFINED = 283,
    T_EXIT = 284,
};
```

### Komentarze:
Komentarze zaczynają się od znaku `#` i są pomijane w trakcie analizy leksykalnej, dlatego nie ma ich zdefiniowanych na liście tokenów ani w automacie.

### Biblioteka standardowa
Biblioteka standardowa będzie obejmować wbudowane funkcje:
- `println(string)`
- `print(string)`
- `string read_line()`
- `print_all_identifiers()`
- `string number_to_string(number)`
- `number string_to_number(string)`
- `boolean number_to_boolean(number)`
- `number boolean_to_number(boolean)`


### Opis automatu parsera:

Program:

![](diagram_generator/diagrams/programStatement.svg)

Functions:

![](diagram_generator/diagrams/functionCall.svg)

![](diagram_generator/diagrams/functionDefinition.svg)

Statements:

![](diagram_generator/diagrams/ifStatement.svg)

![](diagram_generator/diagrams/whileStatement.svg)

![](diagram_generator/diagrams/returnStatement.svg)

![](diagram_generator/diagrams/statement.svg)

Expressions:

![](diagram_generator/diagrams/expression.svg)

![](diagram_generator/diagrams/orExpression.svg)

![](diagram_generator/diagrams/andExpression.svg)

![](diagram_generator/diagrams/equalExpression.svg)

![](diagram_generator/diagrams/relationExpression.svg)

![](diagram_generator/diagrams/additiveExpression.svg)

![](diagram_generator/diagrams/multiplicativeExpression.svg)

![](diagram_generator/diagrams/baseExpression.svg)

Types:

![](diagram_generator/diagrams/identifier.svg)

![](diagram_generator/diagrams/literal.svg)

![](diagram_generator/diagrams/booleanLiteral.svg)

![](diagram_generator/diagrams/numberLiteral.svg)

![](diagram_generator/diagrams/stringLiteral.svg)

Operations:

![](diagram_generator/diagrams/deletion.svg)

![](diagram_generator/diagrams/lambdaAssignment.svg)

![](diagram_generator/diagrams/lambdaDefinition.svg)

Operators:

![](diagram_generator/diagrams/additiveOperator.svg)

![](diagram_generator/diagrams/relationOperator.svg)

![](diagram_generator/diagrams/multiplicativeOperator.svg)

![](diagram_generator/diagrams/andOperator.svg)

![](diagram_generator/diagrams/orOperator.svg)

![](diagram_generator/diagrams/unaryOperator.svg)

![](diagram_generator/diagrams/equalOperator.svg)

Basic:

![](diagram_generator/diagrams/letter.svg)

![](diagram_generator/diagrams/digit.svg)



## Szczegóły implementacyjne <a name="implementacja"></a>

Całość kodu zostanie napisana w C++.

### Główny kontroler 

Moduł głównego kontrolera będzie służył specyfikacji trybu interpretacji (konsola lub plik).
Domyślnie, błędy będą wypisywane w konsoli na standardowe wyjście podczas interpretacji, za pośrednictwem głównego 
kontrolera (błędy parsowania i interpretacji będą wstecznie propagowane tutaj i przekazywane do modułu obsługi błędów).



### Moduł obsługi błędów

Każdy typ błędu interpretacyjnego będzie miał zdefiniowany swój własny wyjątek; w razie napotkania takiego wyjątku
podczas analizy leksykalnej/składniowej lub interpretacji będzie on rzucany, a w konsoli będzie się wyświetlał 
odpowiedni komunikat wraz z linijką i wierszem w kodzie. W przypadku interpretacji z pliku, interpreter przerwie 
działanie pierwszym napotkanym błędzie.

### Moduł analizatora leksykalnego

Analiza leksykalna jest pierwszym etapem parsowania.
W tym miejscu kod zostanie podzielony na tokeny, które zostaną wykorzystane w późniejszych etapach.

### Moduł analizatora składniowego

W module analizatora składniowego zostanie przeprowadzone sprawdzenie składni programu oraz zbudowanie drzewa.

### Moduł interpretera

Moduł interpretera będzie służył wykonywaniu kodu zgodnie z drzewem pozyskanym z analizatora składniowego.
W tym module będzie się znajdować kod odpowiadający za przechowywanie funkcji, istniejących zmiennych i wszystkie 
funkcjonalne właściwości interpretera.

## Uruchamianie <a name="uruchamianie"></a>

Program będzie kompilowany za pomocą narzędzi `cmake` oraz `make`, na systemie `linux`.

Po kompilacji, w katalogu `build/` pojawi się plik wykonywalny `skner`.
Wykonanie polecenia `./skner` w katalogu, spowoduje uruchomienie języka w trybie interpretera.
Wykonanie polecenia `./skner <plik.sk>` zinterpretuje cały kod, wypisze jego wyjście na konsolę, po czym interpreter
zakończy pracę.

## Testowanie <a name="testowanie"></a>

Testy jednostkowe zostaną napisane z pomocą biblioteki `doctest`.

## Dalsze rozszerzenia <a name="rozszerzenia"></a>
W przypadku dalszego rozwijania projektu, przewidziałem powstanie następujących funkcji z biblioteki standardowej umożliwiające live coding (programowanie muzyki):
- `start()`,
- `stop()`,
- `get_tic()`,
- `set_tic(number)`,
- `get_bpm()`,
- `set_bpm(number)`,
- `dac__add_play_function(number)`
- `dac__remove_play_function(number)`
- `sin(number)`,
- `oscillator(number, string)`
- `list_interfaces()`
- `select_interface(string)`
Nie będę ich jednak opisywać, ponieważ wykracza to poza zakres projektu.

W rozszerzeniach przewidziałem także dodanie tablic oraz specjalny typ `sequence`.
