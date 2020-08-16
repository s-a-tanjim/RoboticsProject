String htmlData="<!DOCTYPE html>"
"<html lang='en'>"
"<head>"
"  <meta charset='UTF-8'>"
"  <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"  <link rel='icon' href='data:,'>"
" <title>UVC Car Control</title>"
"  <style>"
"    .section{"
"      border: 1px solid #111;"
"      padding: 20px;"
"      margin: 20px;"
"    }"
"    .switch {"
"      position: relative;"
"      display: inline-block;"
"     width: 60px;"
"      height: 34px;"
"    }"
"    .switch input {"
"      opacity: 0;"
"      width: 0;"
"      height: 0;"
"    }"
"   .slider {"
"      position: absolute;"
"      cursor: pointer;"
"      top: 0;"
"      left: 0;"
"      right: 0;"
"      bottom: 0;"
"      background-color: #ccc;"
"      -webkit-transition: .4s;"
"      transition: .4s;"
"    }"
"    .slider:before {"
"      position: absolute;"
"      content: '';"
"      height: 26px;"
"      width: 26px;"
"      left: 4px;"
"      bottom: 4px;"
"      background-color: white;"
"      -webkit-transition: .4s;"
"      transition: .4s;"
"    }"
"    input:checked+.slider {"
"      background-color: #2196F3;"
"    }"
"    input:focus+.slider {"
"      box-shadow: 0 0 1px #2196F3;"
"    }"
"    input:checked+.slider:before {"
"      -webkit-transform: translateX(26px);"
"      -ms-transform: translateX(26px);"
"      transform: translateX(26px);"
"    }"
"    .slider.round {"
"      border-radius: 34px;"
"    }"
"    .slider.round:before {"
"      border-radius: 50%;"
"    }"
"    #pwmValue {"
"      max-width: 40px;"
"    }"

"    .iframe-container{"
"      width: 100%;"
"      margin-top: 20px;"
"      border-bottom: 1px solid #111;"
"      text-align: center;"
"    }"
"   .iframe-class {"
"      height: 400px;"
"      width: 100%;"
"      border: none;"
"   }"
"    button {"
"      margin: 2px auto;"
"      text-align: center;"
"      background-color: #111;"
"      color: white;"
"      padding: 10px;"
"      border: 1px solid #111;"
"      transition: .3s all;"
"    }"
"    button:hover {"
"      color: #111;"
"      background-color: white;"
"    }"
"  </style>"
"</head>"



"<body>"

"  <div style='text-align: center;'>"
"    <div class='section'>"
"      <div class='iframe-container'>"
"       <h3>Pi Camera</h3>"
"       <iframe class='iframe-class' src='http://192.168.0.100:8000/index.html'></iframe>"
"       <button onClick='ReloadIframe(0)'>Refresh</button>"
"      </div>"
"    </div>"
"    <div class='section'>"
"     <h3>Control Car</h3>"
"     <input onkeydown='car_input_change(event)' id='car_input' type='text'>"
"     <input onchange='car_pwm_input_change()' id='pwmValue' placeholder='PWM' value='100' type='text'>"
"     <p id='car_input_direction'></p>"
"    </div>"
"    <div class='section'>"
"      <h3>UV Switch</h3>"
"      <label class='switch' style='margin-left: 10px;'>"
"        <input onclick='uv_switch()' id='uv_switch_id' type='checkbox'>"
"        <span class='slider round'></span>"
"      </label>"
"    </div>"
"    <div class='section'>"
"      <h3>Advanced Mode</h3>"
"      <label class='switch' style='margin-left: 10px;'>"
"        <input onclick='advanced_mode_switch()' id='advanced_mode_switch_id' type='checkbox'>"
"        <span class='slider round'></span>"
"      </label>"
"    </div>"
"  </div>"

"  <script>"
"    function ReloadIframe(val) {"
"      document.getElementsByClassName('iframe-class')[val].src = document.getElementsByClassName('iframe-class')[val].src;"
"    }"

"    var carInputEvent = document.getElementById('car_input');"
"    var UVSwitchFlag = 0;"
"    var pwmVal = 100;"
"    var currentDirection = 'stop';"
"    var canSendFlag = true;"
"    var superUserMode = false;"

"    function car_input_change(event) {"
"      var x = event.which || event.keyCode;"
"      if(window.innerWidth<600) {"
"        x=carInputEvent.value.charCodeAt(0);"
"      }"
"      if (x === 119 || x === 87) {"
"        document.getElementById('car_input_direction').innerHTML = 'Forward';"
"        sendData('forward');"
"      } else if (x === 115 || x === 83) {"
"        document.getElementById('car_input_direction').innerHTML = 'Backward';"
"        sendData('backward');"
"      } else if (x === 97 || x === 65) {"
"        document.getElementById('car_input_direction').innerHTML = 'Left';"
"        sendData('left');"
"      } else if (x === 100 || x === 68) {"
"        document.getElementById('car_input_direction').innerHTML = 'Right';"
"        sendData('right');"
"      } else if (x === 113 || x === 81) {"
"        document.getElementById('car_input_direction').innerHTML = 'Go Forward';"
"        sendData('goforward');"
"      } else if (x === 101 || x === 69) {"
"        document.getElementById('car_input_direction').innerHTML = 'Stop!';"
"        sendData('stop');"
"      } else if(isNaN(x) && window.innerWidth<600){"
"        document.getElementById('car_input_direction').innerHTML = 'Press Enter!';"
"      } else {"
"        document.getElementById('car_input_direction').innerHTML = 'Invalid!';"
"      }"
"      carInputEvent.value = '';"
"    }"

"    function car_pwm_input_change(){"
"      pwmVal=document.getElementById('pwmValue').value;"
"      if(pwmVal>250)"
"        pwmVal = 250;"
"      if(pwmVal<0 || pwmVal=='' || isNaN(pwmVal))"
"        pwmVal = 0;"
"      sendData(currentDirection);"
"    }"
    
"    function sendData(direction) {"
"      if(canSendFlag) {"
"      canSendFlag=false;"
"      var url = '/'+direction+'?pwm='+pwmVal+'&uvl='+UVSwitchFlag;"   
"      currentDirection = direction;" 
"      /*console.log(url);*/"
"      fetch(url)"
"        .then(res => {"
"          /*console.log(res);*/"
"          console.log('Sent!');"
"        }).catch(err => {"
"          /*console.log(err);*/"
"        })"
"     }"
"    }"

"    function advanced_mode_switch() {"
"      if (document.getElementById('advanced_mode_switch_id').checked)"
"         superUserMode = 1;"
"      else superUserMode = 0;"
"    sendData('supermode');"
"    }"

"    function uv_switch() {"
"     if (document.getElementById('uv_switch_id').checked)"
"        UVSwitchFlag = 1;"
"      else UVSwitchFlag = 0;"
"      sendData(currentDirection);"
"    }"

"    setInterval(() => {"
"      canSendFlag=true;"
"    }, 500);"

"  </script>"
"</body>"
"</html>";