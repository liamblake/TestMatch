Enumerations
============

Types
-----

.. doxygenenum:: Hand
   :project: testmatch

.. doxygenenum:: BowlType
   :project: testmatch

.. doxygenenum:: DismType
   :project: testmatch

.. doxygenenum:: ResultType
   :project: testmatch

.. doxygenenum:: TossChoice
   :project: testmatch

Conversion Functions
--------------------
Each enumeration also includes functions for converting to and from string representations, via the :function:`str` signature. For example,

.. code-block:: c

   BowlType bt = fast_med;
   Arm arm = right;
   str(arm)           // Returns "right"
   chr(arm)           // Return 'r'
   str(bt)            // Returns "fm"
   long_str(arm, bt)  // Returns "right-arm fast-medium"

