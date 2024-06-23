var aVariable = 'a variable';

function aFunction() {
  var inAFunction = 'in aFunction';

  function anInnerFunction() {
    var inAnInnerFunction = 'in an inner function';
    console.log(inAnInnerFunction);
  }

  anInnerFunction();
}

aFunction();