module.exports = function(req,res,next){
  res.send('ok ' + JSON.stringify(req.params));
}
