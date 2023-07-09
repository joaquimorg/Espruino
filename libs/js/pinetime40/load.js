(function(name) {
    __FILE__=name;
    if (!name) name = ".bootcde";
    setTimeout(eval,0,require("Storage").read(name)); // Load app without a reboot    
})
  