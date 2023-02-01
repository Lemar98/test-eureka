const userChecker = require('bindings')('userChecker')

exports.isValidUser = function(username) {
	return userChecker.isValidUser(username);
}