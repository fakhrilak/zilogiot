const express = require('express');
const router = express.Router();
const jwt_decode = require('jwt-decode');
const { Actuators, Sensors,FromSensors } = require('../controllers/actuators');

module.exports = function(io){
    io.on("connection",(socket)=>{
        console.log("========= CONNECTED ==========")
        socket.on("sendto-controlles",async(data)=>{
            await Actuators(socket,data)
        })
        socket.on("sendto-sendsors",async(data)=>{
            await Sensors(socket,data)
        })

        socket.on("from-sensor",async(data)=>{
            await FromSensors(socket,data)
        })
    })

    router.get("/",(req,res)=>{
        return res.status(200).send({
            "message" : "Succes",
            "config_output" : "2",
            "config_input"  : "4"
        })
    })
    return router
}