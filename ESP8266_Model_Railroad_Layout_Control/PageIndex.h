
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }

      .container {
        height: 200px;
        position: relative;
      }

      .center {
        margin: 0;
        position: absolute;
        top: 50%;
        left: 50%;
        -ms-transform: translate(-50%, -50%);
        transform: translate(-50%, -50%);
      }
      
      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 1;
      }

      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #FFA500;
        cursor: pointer;
      }

      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #FFA500;
        cursor: pointer;
      }
	  
	  .btn-group button {
	  
		
		background-color: #FFA500; /* Orange background */
		border: 5px solid grey; 
		color: white; /* White text */
		padding: 10px 40px; /* Some padding */
		cursor: pointer; /* Pointer/hand icon */
		
	  }

/* Clear floats (clearfix hack) */
.btn-group:after {
  content: "";
  clear: both;
  display: table;
}

.btn-group button:not(:last-child) {
  border-right: none; /* Prevent double borders */
}

/* Add a background color on hover */
.btn-group button:hover {
  background-color: #FF8C00;
}
    </style>
  </head>
  <body style="background-color:grey;">
  
	

    <h1>Model Railroad Layout Control</h1>
  

      <p>Value : <span id="v1"></span></p>
	    <p>Direction : <span id="dir"></span></p>

    <div class="slidecontainer">
      <input 
	  type="range" orient="vertical" min="0" max="100" value="0" class="slider" id="myRange"
	  >
	  
	</div>
	
   <div class="container">
      <div class="center"> 	
        	<div class="btn-group">
          <button Forward onclick="forward()"> Forward </button>
          <button Stop onclick= "stop()" > Stop </button>
          <button Reverse onclick="reverse()" > Reverse </button>
        	</div>
	    </div>   
    </div>

    <div class="container">
      <p> Turnout 1 <span id="tt"></span></p>
        <div class="center"> 	
            <div class="btn-group">
            <button Left onclick="tLeft(1)"> Left </button>
            <button Right onclick= "tRight(1)"> Right </button>
            </div>
        </div>   
    </div>
	
	

    <script>
      function sendData(pos) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setPOS?POS="+pos, true);
        xhttp.send();
      }

      function sendDir(dir) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setDir?Dir="+dir, true);
        xhttp.send();
      }

      function sendTNo(tn) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setTNo?TNo="+tn, true);
        xhttp.send();
      }

      function sendTDir(d) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setTDir?TDir="+d, true);
        xhttp.send();
      }
		
		function reverse() {
			dir.innerHTML = "Reverse";
      
      sendDir("-1");		
    }
		
		function forward() {
			dir.innerHTML = "Forward";
      
      sendDir("1");
		}

		function stop()	{
		  slider.value = 0;
		  output.innerHTML = slider.value;
      sendData(output.innerHTML);
		}

    function tLeft(Tn){
      tt.innerHTML = "Left";
      sendTNo(1);
      sendTDir(0);
    }

    function tRight(Tn){
      tt.innerHTML = "Right";
      sendTNo(1);
      sendTDir(1);
    }
  

      var slider = document.getElementById("myRange");
      var output = document.getElementById("v1");
      output.innerHTML = slider.value;
	  
	  
      slider.oninput = function() {
        output.innerHTML = this.value;
        sendData(output.innerHTML);
      }
    </script>

  </body>
</html>

)=====";
