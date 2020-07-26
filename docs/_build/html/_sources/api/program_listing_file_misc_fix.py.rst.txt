
.. _program_listing_file_misc_fix.py:

Program Listing for File fix.py
===============================

|exhale_lsh| :ref:`Return to documentation for file <file_misc_fix.py>` (``misc/fix.py``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: py

   import glob
   def fix(fname):
       with open(fname, "r+") as fp:
           code = fp.read()
           print(fname, code)
           try:
               if not code.splitlines()[1].startswith('#include "core.hpp"'):
                   lines = code.splitlines()
                   lines.insert(1, '#include "core.hpp"')
                   print(lines)
                   fp.seek(0)
                   fp.write("\n".join(lines))
                   fp.truncate()
           except:
               pass
   for fname in glob.glob("*.hpp"):
       fix(fname)
