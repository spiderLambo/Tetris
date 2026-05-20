function navigateTo(url) {
  const overlay = document.createElement("div");
  overlay.style.cssText = `
    position: fixed; inset: 0; z-index: 9999;
    background: #000;
    opacity: 0;
    transition: opacity .4s ease;
  `;
  document.body.appendChild(overlay);

  requestAnimationFrame(() => {
    requestAnimationFrame(() => {
      overlay.style.opacity = "1";
    });
  });

  setTimeout(() => {
    window.location.href = url;
  }, 420);
}

document.addEventListener("click", (e) => {
  const link = e.target.closest("a");
  if (!link || link.origin !== location.origin) return;
  if (link.hash || link.target) return;
  e.preventDefault();
  navigateTo(link.href);
});
