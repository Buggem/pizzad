# pizzad - the pizza delivery daemon
Us programmers need to solve the age old question - how does one order pizza as efficiently as possible?

Enter pizzad. The modern solution to your very propblem.

pizzad is the Pizza Delivery Daemon - a background service that remaps your calculator key for a much better purpose - PIZZA.

It automagically opens your Firefox browser (no Chromium allowed, yet) onto Google so you can
easily and efficiently order pizza, rather then going through the grueling process of typing in
"pizza near me" into your search box.

All programs are designed to fill a space, and pizzad fills a space most elegantly.
As the UNIX motto is, do one thing and do it (_somewhat_) well, and pizzad adheres to that motto.

## Building
No avid CMakers are allowed here - sorry, you'll have to use the bash scripts ;)


I mean, they're pretty simple... aren't they?


`./build.sh` to build, `./install.sh` to install, and `./uninstall.sh` to uninstall.
It couldn't be simpler!

Oh yeah, you'll have to have SystemD and it's dev headers installed. 

But since you are already running SystemD, (guess how I know) you should be fine.


Don't forget to start the service:
```
sudo systemctl start pizzad
```


pizzad will not fail you.
Faithfully yours, pizzad.
