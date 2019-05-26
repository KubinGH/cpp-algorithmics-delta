name = "Dynamiki - Konspekt.md.html"
out = "dp-basics.html"

with open(name, "r") as file:
    s = file.read()
    s = s[s.find('<script type="text/x-mathjax-config">'):]

    s = s.split("\n")
    s.insert(0, "{% block mathjax_preamble %}")
    s.insert(0, "{% extends 'base.html' %}")
    s = s[:-3]
    s.append("{% endblock %}")
    i = s.index("  </head>")
    s.pop(i); s.pop(i)
    s.insert(i, "{% block content %}")
    s.insert(i, "{% endblock %}")
    s = "\n".join(s)
    
    assert '<p><img src="jas-chain.png" alt="Łańcuch w Podciągu Jasia"></p>' in s
    s = s.replace('<p><img src="jas-chain.png" alt="Łańcuch w Podciągu Jasia"></p>',
                  '<p><center><img src="/static/pages/sheets/dp-basics/jas-chain.png" alt="Łańcuch w Podciągu Jasia"></center></p>')
    
    with open(out, "w") as outfile:
        outfile.write(s)
