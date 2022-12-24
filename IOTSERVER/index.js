require('dotenv').config();
const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io',{ rememberTransport: false })(server);
const port = process.env.PORT; ///ENVIRONMEN VARIABLE
const cors = require('cors');
const router = require('./routes')(io);
app.use(cors());
app.use(express.json({limit: '50mb'}));
app.use(express.urlencoded({limit: '50mb'}));

app.use('/zilogiot/api/v2.1/', router);
app.get("/",(req,res)=>{
	return res.send({
		message:"This api v2.1 zilog iot"
	})
})
server.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})