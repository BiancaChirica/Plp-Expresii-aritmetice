# Plp-Expresii-aritmetice
<h1>Parser</h1>

<b>( evaluator de expresii aritmetice )<br>
Chirica Bianca, II B5 FII, 2018 <br>
 </b>
<p>
“A parser is a software component that takes input data (frequently text) and builds a data structure – often some kind of parse tree, abstract syntax tree or other hierarchical structure, giving a structural representation of the input while checking for correct syntax.” (Wikipedia)
 </p>
<br>
Limbajul : C++
<br>
<p>
Programul va primi ca input o expresie aritmetica compusa din cifre ( ‘0' - '9' ), operatorii '+', '-', '*', '/' , paranteze '(' ')' ,functii matematice (sin,cos,sqrt) si variabile si va returna rezultatul in urma comenzii “eval”.
  </p>
  <p>
De exemplu pentru inputul: <br>
X=10 <br>
eval X+(5+2)*7<br>
Y=5 <br>
Eval 4+(5*5+sin(88+10/Y))<br>
Programul va afisa rezultatele : 59 si 30.<br>
 <br>
Exemplu 2 : <br>
Eval 3 + x * 2 / ( 1–5 ) <br>
Programul va afisa eroare. <br>
 <br>
Programul va citi expresia si o va parsa folosind algoritmul shunting-yard, aducand-o in postordine cu ajutorul unei stive si al unei cozi. <br>
Acesta se va baza pe valoarea precedentei operatorilor si asociativitatea lor.
Asociativitate la stanga pentru +,-,*,/ si la dreapta pentru ^ (ridicare la putere). <br>
prec(+) = 2 prec(-) = 2 <br>
prec(∗) = 3 prec(/) = 3 <br>
prec(^)= 4 . <br>
Daca o variabila este declarata de doua ori programul va anunta utilizatorul si va atribui variabilei ultima
valoare introdusa.
