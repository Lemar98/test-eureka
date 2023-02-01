const text = "Привет, это моё тестовое задание. Введи имя пользователя для проверки существования его учетки в твоей ОС";
let index = 0;
	
function type() {
  if (index < text.length) {
    document.getElementById("text").innerHTML += text.charAt(index);
    index++;
    setTimeout(type, 80);
  }
}

type();