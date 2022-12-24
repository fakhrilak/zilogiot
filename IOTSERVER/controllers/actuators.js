exports.Actuators=async(socket,data)=>{
    try{
        return socket.broadcast.emit("tocontrollers-actuator",data)
    }catch(err){
        return socket.emit("error",{"data":err})
    }
}

exports.Sensors=async(socket,data)=>{
    try{
        return socket.broadcast.emit("tocontrollers-sensor",data)
    }catch(err){
        return socket.emit("error",{"data":err})
    }
}

exports.FromSensors=async(socket,data)=>{
    try{
        return await socket.broadcast.emit("sensors-state"+data.pin,data)
    }catch(err){
        console.log(err,"============ INI")
    }
}