function isCompatible(){if(navigator.appVersion.indexOf('MSIE')!==-1&&parseFloat(navigator.appVersion.split('MSIE')[1])<6){return false;}return true;}var startUp=function(){mw.config=new mw.Map(true);mw.loader.addSource({"local":{"loadScript":"/load.php","apiScript":"/api.php"}});mw.loader.register([["site","1380054393",[],"site"],["noscript","1380054393",[],"noscript"],["startup","1453245672",[],"startup"],["filepage","1380054393"],["user.groups","1380054393",[],"user"],["user","1380054393",[],"user"],["user.cssprefs","1453245672",["mediawiki.user"],"private"],["user.options","1453245672",[],"private"],["user.tokens","1380054393",[],"private"],["mediawiki.language.data","1380054393",["mediawiki.language.init"]],["skins.chick","1380054393"],["skins.cologneblue","1380054393"],["skins.modern","1380054393"],["skins.monobook","1380054393"],["skins.nostalgia","1380054393"],["skins.simple","1380054393"],["skins.standard","1380054393"],["skins.vector","1380054393"],["jquery","1380054393"],[
"jquery.appear","1380054393"],["jquery.arrowSteps","1380054393"],["jquery.async","1380054393"],["jquery.autoEllipsis","1380054393",["jquery.highlightText"]],["jquery.badge","1380054393"],["jquery.byteLength","1380054393"],["jquery.byteLimit","1380054393",["jquery.byteLength"]],["jquery.checkboxShiftClick","1380054393"],["jquery.client","1380054393"],["jquery.collapsibleTabs","1380054393"],["jquery.color","1380054393",["jquery.colorUtil"]],["jquery.colorUtil","1380054393"],["jquery.cookie","1380054393"],["jquery.delayedBind","1380054393"],["jquery.expandableField","1380054393",["jquery.delayedBind"]],["jquery.farbtastic","1380054393",["jquery.colorUtil"]],["jquery.footHovzer","1380054393"],["jquery.form","1380054393"],["jquery.getAttrs","1380054393"],["jquery.highlightText","1380054393",["jquery.mwExtension"]],["jquery.hoverIntent","1380054393"],["jquery.json","1380054393"],["jquery.localize","1380054393"],["jquery.makeCollapsible","1416461866"],["jquery.mockjax","1380054393"],[
"jquery.mw-jump","1380054393"],["jquery.mwExtension","1380054393"],["jquery.placeholder","1380054393"],["jquery.qunit","1380054393"],["jquery.qunit.completenessTest","1380054393",["jquery.qunit"]],["jquery.spinner","1380054393"],["jquery.jStorage","1380054393",["jquery.json"]],["jquery.suggestions","1380054393",["jquery.autoEllipsis"]],["jquery.tabIndex","1380054393"],["jquery.tablesorter","1380054393",["jquery.mwExtension"]],["jquery.textSelection","1380054393",["jquery.client"]],["jquery.validate","1380054393"],["jquery.xmldom","1380054393"],["jquery.tipsy","1380054393"],["jquery.ui.core","1380054393",["jquery"],"jquery.ui"],["jquery.ui.widget","1380054393",[],"jquery.ui"],["jquery.ui.mouse","1380054393",["jquery.ui.widget"],"jquery.ui"],["jquery.ui.position","1380054393",[],"jquery.ui"],["jquery.ui.draggable","1380054393",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.droppable","1380054393",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget",
"jquery.ui.draggable"],"jquery.ui"],["jquery.ui.resizable","1380054393",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.selectable","1380054393",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.sortable","1380054393",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.accordion","1380054393",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.autocomplete","1380054393",["jquery.ui.core","jquery.ui.widget","jquery.ui.position"],"jquery.ui"],["jquery.ui.button","1380054393",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.datepicker","1380054393",["jquery.ui.core"],"jquery.ui"],["jquery.ui.dialog","1380054393",["jquery.ui.core","jquery.ui.widget","jquery.ui.button","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.position","jquery.ui.resizable"],"jquery.ui"],["jquery.ui.progressbar","1380054393",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.slider",
"1380054393",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.tabs","1380054393",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.effects.core","1380054393",["jquery"],"jquery.ui"],["jquery.effects.blind","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.bounce","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.clip","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.drop","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.explode","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fade","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fold","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.highlight","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.pulsate","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.scale","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.shake",
"1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.slide","1380054393",["jquery.effects.core"],"jquery.ui"],["jquery.effects.transfer","1380054393",["jquery.effects.core"],"jquery.ui"],["mediawiki","1380054393"],["mediawiki.api","1380054393",["mediawiki.util"]],["mediawiki.api.category","1380054393",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.edit","1380054393",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.parse","1380054393",["mediawiki.api"]],["mediawiki.api.titleblacklist","1380054393",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.watch","1380054393",["mediawiki.api","user.tokens"]],["mediawiki.debug","1380054393",["jquery.footHovzer"]],["mediawiki.debug.init","1380054393",["mediawiki.debug"]],["mediawiki.feedback","1380054393",["mediawiki.api.edit","mediawiki.Title","mediawiki.jqueryMsg","jquery.ui.dialog"]],["mediawiki.htmlform","1380054393"],["mediawiki.notification","1380054393",["mediawiki.page.startup"]],["mediawiki.notify","1380054393"],
["mediawiki.searchSuggest","1416461866",["jquery.autoEllipsis","jquery.client","jquery.placeholder","jquery.suggestions"]],["mediawiki.Title","1380054393",["mediawiki.util"]],["mediawiki.Uri","1380054393"],["mediawiki.user","1380054393",["jquery.cookie","mediawiki.api"]],["mediawiki.util","1416461866",["jquery.client","jquery.cookie","jquery.mwExtension","mediawiki.notify"]],["mediawiki.action.edit","1380054393",["jquery.textSelection","jquery.byteLimit"]],["mediawiki.action.edit.preview","1380054393",["jquery.form","jquery.spinner"]],["mediawiki.action.history","1380054393",[],"mediawiki.action.history"],["mediawiki.action.history.diff","1380054393",[],"mediawiki.action.history"],["mediawiki.action.view.dblClickEdit","1380054393",["mediawiki.util"]],["mediawiki.action.view.metadata","1380054393"],["mediawiki.action.view.rightClickEdit","1380054393"],["mediawiki.action.watch.ajax","1380054393",["mediawiki.page.watch.ajax"]],["mediawiki.language","1380054393",["mediawiki.language.data",
"mediawiki.cldr"]],["mediawiki.cldr","1380054393",["mediawiki.libs.pluralruleparser"]],["mediawiki.libs.pluralruleparser","1380054393"],["mediawiki.language.init","1380054393"],["mediawiki.jqueryMsg","1380054393",["mediawiki.util","mediawiki.language"]],["mediawiki.libs.jpegmeta","1380054393"],["mediawiki.page.ready","1380054393",["jquery.checkboxShiftClick","jquery.makeCollapsible","jquery.placeholder","jquery.mw-jump","mediawiki.util"]],["mediawiki.page.startup","1380054393",["jquery.client","mediawiki.util"]],["mediawiki.page.watch.ajax","1418855653",["mediawiki.page.startup","mediawiki.api.watch","mediawiki.util","mediawiki.notify","jquery.mwExtension"]],["mediawiki.special","1380054393"],["mediawiki.special.block","1380054393",["mediawiki.util"]],["mediawiki.special.changeemail","1439068648",["mediawiki.util"]],["mediawiki.special.changeslist","1380054393",["jquery.makeCollapsible"]],["mediawiki.special.movePage","1380054393",["jquery.byteLimit"]],["mediawiki.special.preferences",
"1380054393"],["mediawiki.special.recentchanges","1380054393",["mediawiki.special"]],["mediawiki.special.search","1419266546"],["mediawiki.special.undelete","1380054393"],["mediawiki.special.upload","1380054393",["mediawiki.libs.jpegmeta","mediawiki.util"]],["mediawiki.special.javaScriptTest","1380054393",["jquery.qunit"]],["mediawiki.tests.qunit.testrunner","1380054393",["jquery.qunit","jquery.qunit.completenessTest","mediawiki.page.startup","mediawiki.page.ready"]],["mediawiki.legacy.ajax","1380054393",["mediawiki.util","mediawiki.legacy.wikibits"]],["mediawiki.legacy.commonPrint","1380054393"],["mediawiki.legacy.config","1380054393",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.IEFixes","1380054393",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.protect","1380054393",["mediawiki.legacy.wikibits","jquery.byteLimit"]],["mediawiki.legacy.shared","1380054393"],["mediawiki.legacy.oldshared","1380054393"],["mediawiki.legacy.upload","1380054393",["mediawiki.legacy.wikibits",
"mediawiki.util"]],["mediawiki.legacy.wikibits","1380054393",["mediawiki.util"]],["mediawiki.legacy.wikiprintable","1380054393"],["skins.erudite","1380054393"],["ext.geshi.local","1380054393"],["ext.confirmAccount","1380054393"]]);mw.config.set({"wgLoadScript":"/load.php","debug":false,"skin":"vector","stylepath":"/skins","wgUrlProtocols":"http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|irc\\:\\/\\/|ircs\\:\\/\\/|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|news\\:|svn\\:\\/\\/|git\\:\\/\\/|mms\\:\\/\\/|\\/\\/","wgArticlePath":"/index.php/$1","wgScriptPath":"","wgScriptExtension":".php","wgScript":"/index.php","wgVariantArticlePath":false,"wgActionPaths":{},"wgServer":"https://cryptocoding.net","wgUserLanguage":"en","wgContentLanguage":"en","wgVersion":"1.20.2","wgEnableAPI":true,"wgEnableWriteAPI":true,"wgMainPageTitle":"Cryptography Coding Standard","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":
"Cryptography Coding Standard","5":"Cryptography Coding Standard talk","6":"File","7":"File talk","8":"MediaWiki","9":"MediaWiki talk","10":"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk"},"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":1,"user":2,"user_talk":3,"cryptography_coding_standard":4,"cryptography_coding_standard_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"image":6,"image_talk":7,"project":4,"project_talk":5},"wgSiteName":"Cryptography Coding Standard","wgFileExtensions":["png","gif","jpg","jpeg"],"wgDBname":"cryptocoding","wgFileCanRotate":true,"wgAvailableSkins":{"erudite":"Erudite","simple":"Simple","myskin":"MySkin","modern":"Modern","monobook":"MonoBook","nostalgia":"Nostalgia","vector":"Vector","pixeled":"Pixeled","standard":"Standard","cologneblue":"CologneBlue","chick":"Chick"},"wgExtensionAssetsPath":
"/extensions","wgCookiePrefix":"cryptocoding","wgResourceLoaderMaxQueryLength":-1,"wgCaseSensitiveNamespaces":[]});};if(isCompatible()){document.write("\x3cscript src=\"/load.php?debug=false\x26amp;lang=en\x26amp;modules=jquery%2Cmediawiki\x26amp;only=scripts\x26amp;skin=vector\x26amp;version=20121204T210731Z\"\x3e\x3c/script\x3e");}delete isCompatible;
/* cache key: cryptocoding:resourceloader:filter:minify-js:7:de0751667ec6275e9457def81cb907b5 */