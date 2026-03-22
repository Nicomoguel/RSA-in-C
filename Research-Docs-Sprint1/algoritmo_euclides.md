# Algoritmo de Euclides

El algoritmo de Euclides fue creado alrededor del año 300 a.C. por el matemático Euclides. Es uno de los algoritmos más eficientes para encontrar el máximo común divisor de dos números. Como lo que estamos buscando es la coprimalidad de dos números muy grandes, el resultado esperado de este algoritmo es 1, es decir, que el máximo común divisor entre *x* y *y* sea 1 y, por lo tanto, sean primos entre sí.

## ¿Cómo funciona?

El algoritmo de Euclides nos dice que `mcd(u, v) = mcd(v, u % v)`, con *u* siempre mayor que *v* al inicio. El proceso se repetirá hasta que *v* sea 0; cuando *v* llegue a 0, el valor que quede en *u* será el máximo común divisor de *u* y *v*.

## ¿Para qué nos sirve?

Previamente encontramos dos números de 128 bits *p* y *q*, además de *n*, que fue el producto de *p* y *q*. En base a *n* encontramos el totiente de Euler de *n*. Ahora, lo que necesitamos para encontrar el exponente público es un número mayor que 1 pero menor que el totiente, y además que el totiente y el exponente sean primos entre sí, es decir, que su `mcd` sea 1.

## ¿Siempre funciona?

La única restricción es que alguno de los números sea 0, ya que de esta forma no se puede calcular el `mcd`. La otra restricción es que alguno de estos números sea 1; sin embargo, no debemos preocuparnos porque la condición excluye estos casos. Además, al trabajar con números tan grandes, es casi imposible que esto suceda.
