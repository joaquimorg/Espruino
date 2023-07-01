(function(mode, cb) {
  var options = {};
  if ("object"==typeof mode) {
    options = mode;
    mode = options.mode;
  }
  var redraw = true;
  if (global.WIDGETS && WIDGETS.back) {
    redraw = false;
    WIDGETS.back.remove(mode && options.back);
  }
  if (Pinetime.btnWatches) {
    Pinetime.btnWatches.forEach(clearWatch);
    delete Pinetime.btnWatches;
  }
  if (Pinetime.swipeHandler) {
    Pinetime.removeListener("swipe", Pinetime.swipeHandler);
    delete Pinetime.swipeHandler;
  }
  if (Pinetime.dragHandler) {
    Pinetime.removeListener("drag", Pinetime.dragHandler);
    delete Pinetime.dragHandler;
  }
  if (Pinetime.touchHandler) {
    Pinetime.removeListener("touch", Pinetime.touchHandler);
    delete Pinetime.touchHandler;
  }
  delete Pinetime.uiRedraw;
  delete Pinetime.CLOCK;
  if (Pinetime.uiRemove) {
    let r = Pinetime.uiRemove;
    delete Pinetime.uiRemove; // stop recursion if setUI is called inside uiRemove
    r();
  }
  g.reset();// reset graphics state, just in case
  if (!mode) return;
  function b() {
    //try{Pinetime.buzz(30);}catch(e){}
  }
  if (mode=="updown") {
    var dy = 0;
    Pinetime.dragHandler = e=>{
      dy += e.dy;
      if (!e.b) dy=0;
      while (Math.abs(dy)>32) {
        if (dy>0) { dy-=32; cb(1) }
        else { dy+=32; cb(-1) }
        //Pinetime.buzz(20);
      }
    };
    Pinetime.on('drag',Pinetime.dragHandler);
    Pinetime.touchHandler = d => {b();cb();};
    Pinetime.btnWatches = [
      setWatch(function() { b();cb(); }, BTN1, {repeat:1, edge:"falling"}),
    ];
  } else if (mode=="leftright") {
    var dx = 0;
    Pinetime.dragHandler = e=>{
      dx += e.dx;
      if (!e.b) dx=0;
      while (Math.abs(dx)>32) {
        if (dx>0) { dx-=32; cb(1) }
        else { dx+=32; cb(-1) }
        //Pinetime.buzz(20);
      }
    };
    Pinetime.on('drag',Pinetime.dragHandler);
    Pinetime.touchHandler = d => {b();cb();};
    Pinetime.btnWatches = [
      setWatch(function() { b();cb(); }, BTN1, {repeat:1, edge:"falling"}),
    ];
  } else if (mode=="clock") {
    Pinetime.CLOCK=1;
    Pinetime.btnWatches = [
      setWatch(Pinetime.showLauncher, BTN1, {repeat:1,edge:"falling"})
    ];
  } else if (mode=="clockupdown") {
    Pinetime.CLOCK=1;
    Pinetime.touchHandler = (d,e) => {
      if (e.x < 120) return;
      b();cb((e.y > 88) ? 1 : -1);
    };
    Pinetime.btnWatches = [
      setWatch(Pinetime.showLauncher, BTN1, {repeat:1,edge:"falling"})
    ];
  } else if (mode=="custom") {
    if (options.clock) Pinetime.CLOCK=1;
    if (options.touch)
      Pinetime.touchHandler = options.touch;
    if (options.drag) {
      Pinetime.dragHandler = options.drag;
      Pinetime.on("drag", Pinetime.dragHandler);
    }
    if (options.swipe) {
      Pinetime.swipeHandler = options.swipe;
      Pinetime.on("swipe", Pinetime.swipeHandler);
    }
    if (options.btn) {
      Pinetime.btnWatches = [
        setWatch(function() { options.btn(1); }, BTN1, {repeat:1,edge:"falling"})
      ];
    } else if (options.clock) {
      Pinetime.btnWatches = [
        setWatch(Pinetime.showLauncher, BTN1, {repeat:1,edge:"falling"})
      ];
    }
  } else
    throw new Error("Unknown UI mode "+E.toJS(mode));
  if (options.remove) // handler for removing the UI (intervals/etc)
    Pinetime.uiRemove = options.remove;
  if (options.redraw) // handler for redrawing the UI
    Pinetime.uiRedraw = options.redraw;
  if (options.back) {
    var touchHandler = (_,e) => {
      if (e.y<36 && e.x<48) {
        e.handled = true;
        options.back();
      }
    };
    Pinetime.on("touch", touchHandler);
    // If a touch handler was needed for setUI, add it - but ignore touches if they've already gone to the 'back' handler
    if (Pinetime.touchHandler) {
      var uiTouchHandler = Pinetime.touchHandler;
      Pinetime.touchHandler = (_,e) => {
        if (!e.handled) uiTouchHandler(_,e);
      };
      Pinetime.on("touch", Pinetime.touchHandler);
    }
    var btnWatch;
    if (Pinetime.btnWatches===undefined) // only add back button handler if there's no existing watch on BTN1
    btnWatch = setWatch(function() {
      btnWatch = undefined;
      options.back();
    }, BTN1, {edge:"falling"});
    WIDGETS = Object.assign({back:{
      area:"tl", width:24,
      draw:e=>g.reset().setColor("#f00").drawImage(atob("GBiBAAAYAAH/gAf/4A//8B//+D///D///H/P/n+H/n8P/n4f/vwAP/wAP34f/n8P/n+H/n/P/j///D///B//+A//8Af/4AH/gAAYAA=="),e.x,e.y),
      remove:(noclear)=>{
        if (btnWatch) clearWatch(btnWatch);
        Pinetime.removeListener("touch", touchHandler);
        if (!noclear) g.reset().clearRect({x:WIDGETS.back.x, y:WIDGETS.back.y, w:24,h:24});
        delete WIDGETS.back;
        if (!noclear) Pinetime.drawWidgets();
      }
    }},global.WIDGETS);
    if (redraw) Pinetime.drawWidgets();
  } else { // If a touch handler was needed for setUI, add it
    if (Pinetime.touchHandler)
      Pinetime.on("touch", Pinetime.touchHandler);
  }
})
