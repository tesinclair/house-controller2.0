brightnessScrollerBtn = document.querySelector(".brightnessBtn")
brightnessScroller = document.querySelector(".brightness")
colors = document.querySelector(".colors");
placeholder = document.querySelector(".placeholder");

function onLoad(){
	brightness = localStorage.getItem("brightness")
	lightToggle = localStorage.getItem("light-toggle")
	if (brightness){
		brightnessScroller.value = brightness;
	}
	if (lightToggle){
		colors.classList.toggle("hide");
		placeholder.classList.toggle("hide");
	}
}

brightnessScroller.addEventListener('input', (e) =>{
	brightnessScrollerBtn.textContent = brightnessScroller.value;
});

brightnessScrollerBtn.addEventListener('click', (e) =>{
	brightness = parseInt(brightnessScroller.value)/100
	localStorage.setItem("brightness", brightnessScroller.value);
	window.location.href = "/set?brightness=" + brightness;
});

light = document.querySelector(".light")

light.addEventListener('click', (e) => {
	localStorage.setItem("light-toggle", colors.classList.contains("hide"))

	colors.classList.toggle('hide');
	placeholder.classList.toggle('hide');
});
