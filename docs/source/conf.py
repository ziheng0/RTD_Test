# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Quecopen'
copyright = '2025, Admin'
author = 'Admin'
release = '0.5'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'myst_parser',
    "sphinxcontrib.mermaid",
    "sphinx_copybutton",
    'breathe',
    
     ]

breathe_projects = { "quecopen": "../doxygen/xml" }
breathe_default_project = "quecopen"

source_suffix = {
            '.rst': 'restructuredtext',
            '.md': 'markdown',
   }

myst_enable_extensions = [
           "tasklist",
           "deflist",
           "dollarmath",
   ]

templates_path = ['_templates']
exclude_patterns = []

html_logo = './_static/images/quectel-logo.png'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_css_files = [
    'css/custom.css',
]
