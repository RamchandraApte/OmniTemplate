
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_docs_conf.py.rst.txt:

Program Listing for File program_listing_file_docs_conf.py.rst.txt
==================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_docs_conf.py.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_docs_conf.py.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_docs_conf.py:
   
   Program Listing for File conf.py
   ================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_docs_conf.py>` (``docs/conf.py``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: py
   
      # The `extensions` list should already be in here from `sphinx-quickstart`
      extensions = [
          # there may be others here already, e.g. 'sphinx.ext.mathjax'
          'breathe',
          'exhale'
      ]
      
      # Setup the breathe extension
      breathe_projects = {
          "OmniTemplate": "./xml"
      }
      breathe_default_project = "OmniTemplate"
      
      # Setup the exhale extension
      exhale_args = {
          # These arguments are required
          "containmentFolder":     "./api",
          "rootFileName":          "library_root.rst",
          "rootFileTitle":         "Library API",
          "doxygenStripFromPath":  "..",
          # Suggested optional arguments
          "createTreeView":        True,
          # TIP: if using the sphinx-bootstrap-theme, you need
          # "treeViewIsBootstrap": True,
          "exhaleExecutesDoxygen": True,
          "exhaleDoxygenStdin":    "INPUT = .."
      }
      
      # Tell sphinx what the primary language being documented is.
      primary_domain = 'cpp'
      
      # Tell sphinx what the pygments highlight language should be.
      highlight_language = 'cpp'
