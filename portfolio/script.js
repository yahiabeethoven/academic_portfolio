
// taken from assignment 4
function qImgLoad() {
    document.getElementsByClassName('qFallback')[0].style.backgroundColor = "transparent";
}



let highschool1 = document.getElementById("highschool1");
let sports1 = document.getElementById("sports1");
let food1 = document.getElementById("food1");
let program1 = document.getElementById("program1");



highschool1.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text1").innerText = "I attended highschool at Hayah International Academy in Cairo, Egypt. I took the IB Diploma from there as a Salutatorian in 2019. I joined activities such as MUN, Student Council, and acting.";
	document.getElementById("highschool").style.backgroundColor = "black";
	document.getElementById("highschool").style.color = "white";
})

highschool1.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text1").innerText = "";
	document.getElementById("highschool").style.backgroundColor = "transparent";
	document.getElementById("highschool").style.transition = "0.7s ease-out";
})



sports1.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text2").innerText = "My favorite sports are squash, handball, and football. I participated in the first two on a professional level.";
	document.getElementById("sports").style.backgroundColor = "black";
	document.getElementById("sports").style.color = "white";
})

sports1.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text2").innerText = "";
	document.getElementById("sports").style.backgroundColor = "transparent";
	document.getElementById("sports").style.transition = "0.7s ease-out";
})




food1.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text3").innerText = "My favorite food is seafood, and sushi is number one on the list. I like to eat by dipping into the Teriyaki sauce, and I prefer maki and dynamite rolls over the classic Nigiri.";
	document.getElementById("food").style.backgroundColor = "black";
	document.getElementById("food").style.color = "white";

})

food1.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text3").innerText = "";
	document.getElementById("food").style.backgroundColor = "transparent";
	document.getElementById("food").style.transition = "0.7s ease-out";
})




program1.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text4").innerText = "I participated in a life-changing program titled Yale Young Global Scholars at Yale University in 2018 about Sustainable Development and Social Entrepreneurship.";
	document.getElementById("program").style.backgroundColor = "black";
	document.getElementById("program").style.color = "white";
})

program1.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text4").innerText = "";
	document.getElementById("program").style.backgroundColor = "transparent";
	document.getElementById("program").style.transition = "0.7s ease-out";
})