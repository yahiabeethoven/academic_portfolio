console.log("Yo, how's life?");

// fire.style.color = "orange";

let iconTheme1 = document.getElementById("fire");

iconTheme1.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text1").innerText = " Episodes which revolve around heating up objects in the lab or burning them using our Bunsen burner to yield exciting results are very intense! These experiments need to be executed with extreme caution as they may incur damages. "
	// document.getElementById("fire").border ="solid white"
})
iconTheme1.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text1").innerText = ""
})

let iconTheme2 = document.getElementById("water");

iconTheme2.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text2").innerText = " Episodes which revolve around the exploration of the properties of different liquids (especially the fountain of life; water) are extremely fun! These experiments are usually the most appealing for the younger kids and are quite engaging. "
})

iconTheme2.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text2").innerText = ""
})

let iconTheme3 = document.getElementById("electricity");

iconTheme3.addEventListener('mouseenter', () => {
	document.getElementById("ghost-text3").innerText = " Episodes which revolve around the exploration of the properties of electricity and circuits are good challenges for students. They help them grasp abstract concepts suh as voltage, power, and the ampere. "
})

iconTheme3.addEventListener('mouseleave', () => {
	document.getElementById("ghost-text3").innerText = ""
})



// -----------------------------------------------------------------------------------------------------------------------------------


/*<!-- this part has been copied from bootstrap to make a slideshow of picturesfrom nature. Here is the URL of the website: https://www.w3schools.com/howto/howto_js_slideshow.asp-->*/
var slideIndex = 1;
showSlides(slideIndex);

// Next/previous controls
function plusSlides(n) {
  showSlides(slideIndex += n);
}

// Thumbnail image controls
function currentSlide(n) {
  showSlides(slideIndex = n);
}

function showSlides(n) {
  var i;
  var slides = document.getElementsByClassName("mySlides");
  var dots = document.getElementsByClassName("dot");
  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}
  for (i = 0; i < slides.length; i++) {
      slides[i].style.display = "none";
  }
  for (i = 0; i < dots.length; i++) {
      dots[i].className = dots[i].className.replace(" active", "");
  }
  slides[slideIndex-1].style.display = "block";
  dots[slideIndex-1].className += " active";
}