const express = require('express');
const app = express();
const checker = require('./user-checker');
const urlencodedParser = express.urlencoded({extended: false});

const host = 'localhost';
const port = 3000;

app.use(express.static('pages/main page'));
app.use(express.static('pages/found page'));
app.use(express.static('pages/not found page'));

app.get('/', (req, res) => res.sendFile(__dirname + "/pages/main page/index.html"));

app.post('/', urlencodedParser, (req, res) => {
	if(!req.body) 
		return res.sendStatus(400);
	
	let user = req.body.user;
	let exists = checker.isValidUser(user);
	let page = exists ? "/pages/found page/user-found.html" : "/pages/not found page/user-not-found.html"
	
	res.sendFile(__dirname + page);
});

app.listen(port, host, () => console.log(`Сервер запущен по адресу http://${host}:${port}`));