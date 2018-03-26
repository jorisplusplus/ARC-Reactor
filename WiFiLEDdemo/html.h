const char index_html[] PROGMEM = R"(

<head>
  <title>WiFi LED Demo</title>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
  <style>
    .color-sel {
      width: 24px;
      height: 24px;
      text-align: center;
    }

    .pixel-sel {
      width: 48px;
      height: 48px;
      background-color: black;
    }

    button {
      font-size: 16px;
    }

    p {
      font-size: 18px;
      font-style: normal;
      line-height: 0px;
    }

    table {
      border-color: lightgray;
      border-collapse: collapse;
    }
  </style>
</head>

<body>
  <script>
    var nh = 12,
      i, j, cc = 'rgb(255, 255, 255)';
    var cc_elem;

    function w(s) {
      document.write(s);
    }

    function id(s) {
      return document.getElementById(s);
    }

    function mark(e) {
      e.innerHTML = '&#10004;';
    }

   
  </script>
  <hr />
  <p>Set pixel color: <button id='btn_submit'><b>Submit</b></button></p>
  <script>

    id('btn_sendtext').addEventListener('click', function(e) {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
          var jd = JSON.parse(xhr.responseText);
          // jd stores the response data
        }
      };
      comm = 'http://192.168.4.1/cc?scrolltext=' + document.getElementById("scrolltext").value+'&wait='+document.getElementById("scrollspeed").value+'&color='+document.getElementById("scrollcolor").value.substring(1);
      xhr.open('GET', comm, true);
      xhr.send(null);
    });

    function send_comm() {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
          var jd = JSON.parse(xhr.responseText);
          // jd stores the response data
        }
      };
      comm = 'http://192.168.4.1/cc';
      xhr.open('GET', comm, true);
      xhr.send(null);
    }

    id('btn_submit').addEventListener('click', function(e) {
      send_comm();
    });

   
  </script>
</body>)";
