function randomchar(length) {
  var result = "";
  var characters =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  var charactersLength = characters.length;
  for (var i = 0; i < length; i++) {
    result += characters.charAt(Math.floor(Math.random() * charactersLength));
  }
  return result;
}

function apparait(element) {
  const textNode = [...element.childNodes].find(
    (n) => n.nodeType === Node.TEXT_NODE,
  );

  const texte = textNode.textContent.trim();
  for (let i = 0; i <= texte.length; i++) {
    setTimeout(() => {
      textNode.textContent = texte.slice(0, i) + randomchar(texte.length - i);
    }, i * 50);
  }
}

document.querySelectorAll("li:not(:has(*)), summary").forEach((el) => {
  console.log(el);
  apparait(el);
});
