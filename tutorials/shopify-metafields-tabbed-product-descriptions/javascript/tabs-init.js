// Alternate/duplicate JavaScript initializer that handles tab clicks and manages active tab and pane classes for transitions.
//
// Full tutorial: https://shillehtek.com/blogs/news/shopify-metafields-tabbed-product-descriptions
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

document.addEventListener('DOMContentLoaded', function () {
  var tabs = document.querySelectorAll('.nav a');
  tabs.forEach(function (tab) {
    tab.addEventListener('click', function (event) {
      event.preventDefault();
      var activeTabs = document.querySelectorAll('.active');
      activeTabs.forEach(function (tab) {
        tab.classList.remove('active');
      });

      tab.parentElement.classList.add('active');
      var anchor = event.target;
      var activePaneID = anchor.getAttribute('href');
      var activePane = document.querySelector(activePaneID);
      document.querySelectorAll('.tab-pane').forEach(function (pane) {
        pane.classList.remove('active');
        pane.classList.remove('in');
      });
      activePane.classList.add('active');
      setTimeout(function () {
        activePane.classList.add('in');
      }, 250);
    });
  });
});
