document.addEventListener('DOMContentLoaded', function () {
  const slides = document.querySelectorAll('.slide');
  const leftArrow = document.getElementById('leftArrow');
  const rightArrow = document.getElementById('rightArrow');
  let currentSlide = 0;

  function showSlide(idx) {
    slides.forEach((slide, i) => {
      slide.style.display = (i === idx) ? 'block' : 'none';
    });
    currentSlide = idx;
  }

  leftArrow.addEventListener('click', function () {
    if (currentSlide > 0) {
      showSlide(currentSlide - 1);
    }
  });

  rightArrow.addEventListener('click', function () {
    if (currentSlide < slides.length - 1) {
      showSlide(currentSlide + 1);
    }
  });

  // Initialize
  showSlide(0);
}); 