const { exec } = require("child_process")

runFunc()

function runFunc() {
  const dirName = 'HelloWorld'
  const fileName = 'main.cpp'
  const compilatorName = 'main'
  const cores = '3'

  const locate = 'cd ../' + dirName
  const createCompilator = 'mpic++ ' + fileName + ' -o ' + compilatorName
  const runCompilator = 'mpirun -n ' + cores + ' ' + compilatorName

  const bashCommand = locate + ' && ' + createCompilator + ' && ' + runCompilator
  exec(bashCommand, (err, stdout, stderr) => {
    if (err) {
      console.log(err)
      return
    }
    console.log("STDOUT: \n" + stdout)
    console.log("STDERR: \n" + stderr)
  })
}