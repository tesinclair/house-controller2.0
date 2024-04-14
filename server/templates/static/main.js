brightnessScrollerBtn = document.querySelector(".brightnessBtn")
brightnessScroller = document.querySelector(".brightness")

function onLoad(){
	brightness = localStorage.getItem("brightness")
	if (brightness){
		brightnessScroller.value = brightness;
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


