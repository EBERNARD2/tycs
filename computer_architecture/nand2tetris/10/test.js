function function1() {
  console.log("start of function 1");
  function2();
  console.log("end of function 1");
}

function function2() {
  console.log("start of function 2");
  function3();
  console.log("end of function 2");
}

function function3() {
  console.log("start of function 3");
  console.log("end of function 3");
}


function1();
