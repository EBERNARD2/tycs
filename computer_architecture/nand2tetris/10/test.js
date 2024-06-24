function aFunction1() {
  var inAFunction1 = 'in aFunction1';

  function anInnerFunction() {
    var inAnInnerFunction1 = 'in anInnerFunction1';
    console.log(inAFunction1);
  }

  anInnerFunction();
}

aFunction1();

function aFunction2() {
  var inAFunction2 = 'in aFunction2';

  function andInnerFunction2() {
    var inAnInnerFunction2 = 'in anInnerFunction2';
    // console.log(inAFunction2);
  }

  andInnerFunction2();
}

aFunction2();




// 1.. line 5. inAnInnerFunction1 var
//             Global - local - closure(afunction1)

// 1.. line 5. inAnInnerFunction2 var
//             Global - local - closure(afunction2)